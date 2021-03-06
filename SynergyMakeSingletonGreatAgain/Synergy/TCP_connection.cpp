#include "TCP_connection.h"

typedef boost::shared_ptr<TCP_connection> pointer;

TCP_connection::TCP_connection(boost::asio::io_service& io_service) : socket_(io_service) {}

void TCP_connection::handle_read(const boost::system::error_code &, size_t) 
{
	std::string message = InputHandler::Instance().recievedMessage;
	std::cout << message << std::endl;
	Emulator::ParseMSG(message);
}

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
	InputHandler::Instance().hasConnection.store(true);
	socket().async_read_some(
		boost::asio::buffer(InputHandler::Instance().recievedMessage),
		boost::bind(&TCP_connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	while (InputHandler::Instance().hasConnection.load())
	{
		if (!InputHandler::Instance().sentMessage.empty())
		{
			try
			{
				//std::cout << InputHandler::Instance().sentMessage.front() << std::endl;
				boost::asio::write(socket(),
					boost::asio::buffer(InputHandler::Instance().sentMessage.front()));
				InputHandler::Instance().sentMessage.pop();
			}
			catch (std::exception &ex)
			{
				std::cout << "Client disconnected" << std::endl;
				InputHandler::Instance().hasConnection.store(false);
				InputHandler::Instance().isCurrentComputerDisabled.store(false);
				mutex_.unlock();
				return;
			}
		}
	}
}
