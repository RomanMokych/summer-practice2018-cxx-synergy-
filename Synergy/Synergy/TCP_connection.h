#pragma once
#include "InputHandler.h"
#include "Emulator.h"
#include <mutex>
#include <condition_variable>

class TCP_connection : public boost::enable_shared_from_this<TCP_connection>
{
private:
	TCP_connection(boost::asio::io_service& io_service);
	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/);
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	tcp::socket socket_;

public:
	

	typedef boost::shared_ptr<TCP_connection> pointer;
	static pointer create(boost::asio::io_service& io_service);
	tcp::socket& socket();
	void start();
};

