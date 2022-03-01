#pragma once

#include <boost/asio.hpp>

namespace Engine {
class Session;
} // namespace Connection

namespace Engine {

class IServer : boost::noncopyable {
public:
	IServer(boost::asio::io_context& io_context, 
	        const boost::asio::ip::tcp::endpoint& endpoint);

	void Start();

	virtual void OnAccepted(boost::asio::ip::tcp::socket&& socket) = 0;

	virtual void OnError(const boost::system::error_code& ec) = 0;

protected:
	boost::asio::io_context& io_context_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

} // namespace Engine

