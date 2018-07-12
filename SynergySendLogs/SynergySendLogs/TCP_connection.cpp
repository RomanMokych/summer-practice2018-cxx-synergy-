#include "TCP_connection.h"

typedef boost::shared_ptr<TCP_connection> pointer;

TCP_connection::TCP_connection(boost::asio::io_service& io_service) : socket_(io_service){}

void TCP_connection::handle_read(const boost::system::error_code &, size_t){}

void TCP_connection::handle_write(const boost::system::error_code & error, size_t bytes_transferred)
{
	if (InputHandler::Instance().sentMessage != "")
	{
		std::cout << "Handle Write of connection\n";
		if (error && error != boost::asio::error::eof) 
		{
			std::cout << "Error: " << error.message() << "\n";
			return;
		}
		InputHandler::Instance().sentMessage;
		socket().write_some(boost::asio::buffer(InputHandler::Instance().sentMessage));
		InputHandler::Instance().sentMessage = "";
	}
}

pointer TCP_connection::create(boost::asio::io_service & io_service)
{
	return pointer(new TCP_connection(io_service));
}

tcp::socket & TCP_connection::socket()
{
	return socket_;
}

void TCP_connection::start()
{
	boost::asio::async_write(socket_, message_,
		boost::bind(&TCP_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}
