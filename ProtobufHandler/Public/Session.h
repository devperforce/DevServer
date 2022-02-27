#pragma once

#include "Connection/Public/Session.h"

namespace google {
namespace protobuf {
class Message;
} // namespace protobuf
} // namespace google

namespace Common {

class Session : public Engine::Session {
public:
    Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket&& socket) 
        : Engine::Session(io_context, std::move(socket)) {
    }
    virtual ~Session () = default;

    void Send(std::shared_ptr<google::protobuf::Message> msg);

protected:
    void OnRecv(int32_t protocol_id, const BYTE* buf, uint32_t size) override;
};

} // namespace Common