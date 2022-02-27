#include "pch.h"
#include "Connection/Public/Session.h"

namespace Engine {

Session::Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket&& socket) 
    : strand_(io_context), socket_(std::move(socket)) {

}

void Session::Start() {
    OnConnected();
    ReadHeader();
}

void Session::Close() {
    strand_.dispatch([this, self = shared_from_this()]{
        socket_.shutdown(boost::asio::socket_base::shutdown_both);
        socket_.close();
    });
    OnClosed();
}

void Session::ReadHeader() {
    boost::asio::async_read(socket_,
        boost::asio::buffer(&header_, kHeaderLength),
        [this, self = shared_from_this()](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec) {
                OnDisconnected(ec);
                return;
            }
            ReadBody();
        });
}

void Session::ReadBody() {
    boost::asio::async_read(socket_,
        boost::asio::buffer(data_, header_),
        [this, self = shared_from_this()](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec) {
                OnDisconnected(ec);
                return;
            }

            int32_t protocol_id = std::numeric_limits<int32_t>::max();
            Buffer protocol;
            std::memcpy(&protocol_id, data_.data(), kProtocolLength);

            const uint32_t protocol_length = header_ - kProtocolLength;
            if (protocol_length >= protocol.size()) {
                LOG_ERROR("Unable to read body. protocol_length: {}", protocol_length);
                OnDisconnected(ec);
                return;
            }

            std::memcpy(&protocol, data_.data() + kProtocolLength, protocol_length);

            OnRecv(protocol_id, protocol.data(), protocol_length);
            
            ReadHeader();
        });
}

void Session::Send(BufferInfo buffer_info) {
    strand_.dispatch([this, self = shared_from_this(), data_info = std::move(buffer_info)] {
        const bool write_in_progress = !send_queue_.empty();
        send_queue_.push_back(data_info);
        if (!write_in_progress)
        {
            Send();
        }
    });
}

void Session::Send() {
    const auto data_info = send_queue_.front();
    boost::asio::async_write(socket_,
        boost::asio::buffer(data_info.buffer, data_info.length),
        [this, self = shared_from_this()](boost::system::error_code ec, std::size_t /*length*/)
        {
            //여기서 불리는 callback 이 보내기전에 스레드랑 같은것인지 체크
            if (ec) {
                OnError(ec);
                return;
            }

            // 큐를 보고 있으면 다시 보냄
            strand_.dispatch([this, self] {
                send_queue_.pop_front();
                if (!send_queue_.empty()) {
                    Send();
                }
            });
        });
}

boost::asio::io_context::strand& Session::strand () {
    return strand_;
}

} // namespace Engine
