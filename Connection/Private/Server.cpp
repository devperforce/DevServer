#include "pch.h"
#include "Connection/Public/Server.h"

namespace Engine {

IServer::IServer(boost::asio::io_context& io_context,
                const boost::asio::ip::tcp::endpoint& endpoint) 
    : io_context_(io_context), acceptor_(io_context, endpoint) {
}

void IServer::Start() {
    try {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
            {
                if (ec) {
                    OnError(ec);
                }
                else {
                    OnAccepted(std::move(socket));
                }

                Start();
            });
    } catch (...) {
        //LOG_ERROR("fuck");
    }
}

} // namespace Connection
