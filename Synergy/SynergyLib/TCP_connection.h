#pragma once
#include "Messenger.h"
#include "InputHandler.h"
#include "Emulator.h"

class TCP_connection : public std::enable_shared_from_this<TCP_connection>
{
private:
	TCP_connection(boost::asio::io_service& io_service);
	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/);
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	tcp::socket socket_;
	void ContinueReading();
public:
	typedef std::shared_ptr<TCP_connection> pointer;
	static pointer create(boost::asio::io_service& io_service);
	tcp::socket& socket();
	void start();
	void SetConnections();
};

