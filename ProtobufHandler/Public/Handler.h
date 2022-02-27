#pragma once

#include "Protobuf/Generated/common.pb.h"

namespace Engine {
class Session;
} // namespace Connection

namespace Common {

class IHandler {
public:
    virtual ~IHandler() = default;
    virtual bool OnHandle(const unsigned char* buf, uint32_t size, std::shared_ptr<Engine::Session> session) = 0;

    static constexpr size_t kMaxHandlerSize = 1000;
    using Handlers = std::array<std::shared_ptr<IHandler>, kMaxHandlerSize>;
    static Handlers& handlers();
};

// enable_if base_of(ISession)
template <typename Message, typename Session >
class Handler : public IHandler {
public:
    using Callback = void(*)(std::shared_ptr<Message>, std::shared_ptr<Session> session);

    virtual ~Handler() = default;

    static void Register(Callback callback) {
        static_assert(std::is_base_of<Engine::Session, Session>::value, "Session doesn't inherit from ISession!");

        const ProtocolId packet_id = Message::descriptor()->options().GetExtension(type_enum);
        auto handler = std::make_shared<Handler<Message, Session>>();
        handler->callback_ = callback;
        auto& handlers = IHandler::handlers();
        handlers[packet_id] = handler;
    }

    bool OnHandle(const unsigned char* buf, uint32_t size, std::shared_ptr<Engine::Session> session) override {
        auto msg = std::make_shared<Message>();
        const bool result = msg->ParseFromArray(buf, size);
        if(!result) {
            return false;
        }

        callback_(msg, std::static_pointer_cast<Session>(session));
        return true;
    }

    Callback callback_;
};

} // namespace Common