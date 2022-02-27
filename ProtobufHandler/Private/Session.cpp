#include "pch.h"
#include "ProtobufHandler/Public/Session.h"

#include "ProtobufHandler/Public/Handler.h"


namespace Common {

void Session::OnRecv(int32_t protocol_id, const BYTE* buf, uint32_t size) {
    
    const auto& handler = IHandler::handlers()[protocol_id];

    if(handler == nullptr) {
        LOG_ERROR("Invalid protocol. protocol_id: {}", protocol_id);
        Close();
        return;
    }

    if(!handler->OnHandle(buf, size, shared_from_this())) {
        LOG_ERROR("Unable to parse from array. protocol_id: {}, size: {}", protocol_id, size);
        Close();
    }
}

void Session::Send(std::shared_ptr<google::protobuf::Message> msg) {
    BufferInfo buffer_info;

    const uint32_t msg_size = static_cast<uint32_t>(msg->ByteSizeLong());
    if (kMaxBodyLength <= msg_size) {
        LOG_ERROR("[Send] msg size: {0}", msg_size);
        return;
    }
    buffer_info.length = kHeaderLength + kProtocolLength + msg_size;
    const uint32_t header_length = kProtocolLength + msg_size;
    const uint32_t protocol_id = msg->GetDescriptor()->options().GetExtension(type_enum);

    std::memcpy(buffer_info.buffer.data(), &header_length, kHeaderLength);
    std::memcpy(buffer_info.buffer.data() + kHeaderLength, &protocol_id, kProtocolLength);
    msg->SerializeToArray(buffer_info.buffer.data() + kHeaderLength + kProtocolLength, msg_size);
    Engine::Session::Send(buffer_info);
}

} // namespace Common
                                                                                                                               