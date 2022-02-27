#pragma once

#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <deque>

namespace Engine {

class Session : public std::enable_shared_from_this<Session>, boost::noncopyable {
public:
	static constexpr uint32_t kHeaderLength = sizeof(int32_t);
	static constexpr uint32_t kProtocolLength = sizeof(int32_t);
	static constexpr uint32_t kMaxBodyLength = 512 * 8;

	using Buffer = std::array<BYTE, kProtocolLength + kMaxBodyLength>;

	struct BufferInfo {
		size_t length;
		Buffer buffer;
	};

	Session(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket&& socket);
	virtual ~Session() = default;

	void Start();
	void Close();

	virtual void OnConnected() = 0;
	virtual void OnDisconnected(const boost::system::error_code& ec) = 0;

	virtual void OnRecv(int32_t protocol_id, const BYTE* protocol, uint32_t protocol_size) = 0;

	virtual void OnError(const boost::system::error_code& ec) = 0;
	virtual void OnClosed() = 0;

	boost::asio::io_context::strand& strand ();
	
protected:
	void Send (BufferInfo buffer_info);

	boost::asio::io_context::strand strand_;
private:
	void ReadHeader();
	void ReadBody();

	void Send();

	boost::asio::ip::tcp::socket socket_;

	int32_t header_;
	Buffer data_;

	std::deque<BufferInfo> send_queue_;
};

} // namespace Engine
