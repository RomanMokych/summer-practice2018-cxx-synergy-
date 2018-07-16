#include "TCP_connection.h"

typedef boost::shared_ptr<TCP_connection> pointer;

TCP_connection::TCP_connection(boost::asio::io_service& io_service) : socket_(io_service){}

void TCP_connection::handle_read(const boost::system::error_code &, size_t){}

void TCP_connection::handle_write(const boost::system::error_code & error, size_t bytes_transferred){}

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
	while (true)
	{
		if (InputHandler::Instance().sentMessage != "")
		{
			try
			{
				boost::asio::write(socket(),
				boost::asio::buffer(InputHandler::Instance().sentMessage));
				InputHandler::Instance().sentMessage = "";
			}
			catch (std::exception &ex)
			{
				std::cout << "Client disconnected" << std::endl;
				return;
			}
		}
	}
}
