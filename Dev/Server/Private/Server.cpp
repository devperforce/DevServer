#include "pch.h"
#include "Dev/Server/Public/Server.h"
#include "Content/Protocol/Public/Session.h"

namespace Content {

Server::Server(
    boost::asio::io_context& io_context,
    const boost::asio::ip::tcp::endpoint& endpoint)
    : Engine::IServer(io_context, endpoint) {
    
}

void Server::OnAccepted(boost::asio::ip::tcp::socket&& socket) {
    std::make_shared<Protocol::Session>(io_context_, std::move(socket))->Start();
}

void Server::OnError(const boost::system::error_code& ec) {

}

} // namespace Content
