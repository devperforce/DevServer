#pragma once

#include "Connection/Public/Server.h"

namespace Content {

class Server : public Engine::IServer {
public:
    Server(boost::asio::io_context& io_context,
           const boost::asio::ip::tcp::endpoint& endpoint);
    virtual ~Server() = default;

    void OnAccepted(boost::asio::ip::tcp::socket&& socket) override;
    void OnError(const boost::system::error_code& ec) override;
};

} // namespace Content