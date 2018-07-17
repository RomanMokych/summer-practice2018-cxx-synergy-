#include "TCP_connection.h"

typedef boost::shared_ptr<TCP_connection> pointer;

TCP_connection::TCP_connection(boost::asio::io_service& io_service) : socket_(io_service) {}

void TCP_connection::handle_read(const boost::system::error_code &, size_t) {}

void TCP_connection::handle_write(const boost::system::error_code & error, size_t bytes_transferred) {}

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
	boost::asio::ip::tcp::no_delay noDelayOption(true);
	socket_.set_option(noDelayOption);
	InputHandler::Instance().hasConnection = true;
	while (InputHandler::Instance().hasConnection)
	{
		if (!InputHandler::Instance().sentMessage.empty())
		{
			try
			{
				std::cout << InputHandler::Instance().sentMessage.front() << std::endl;
				boost::asio::write(socket(),
					boost::asio::buffer(InputHandler::Instance().sentMessage.front()));
				InputHandler::Instance().sentMessage.pop();
			}
			catch (std::exception &ex)
			{
				std::cout << "Client disconnected" << std::endl;
				InputHandler::Instance().hasConnection = false;
				InputHandler::Instance().isCurrentComputerDisabled = false;
				return;
			}
		}
	}
}
