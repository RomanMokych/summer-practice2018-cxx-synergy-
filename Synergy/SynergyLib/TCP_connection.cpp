#include "TCP_connection.h"

typedef std::shared_ptr<TCP_connection> pointer;

TCP_connection::TCP_connection(boost::asio::io_service& io_service) : socket_(io_service) {}

void TCP_connection::handle_read(const boost::system::error_code &error, size_t)
{
	if (!error)
	{
		std::cout << Messenger::Instance().recievedMessage << std::endl;
		Emulator::ParseMSG(Messenger::Instance().recievedMessage);
		ContinueReading();
	}
	else
	{
		std::cout << "Client disconnected" << std::endl;
		InputHandler::Instance().hasConnection = false;
		InputHandler::Instance().isCurrentComputerDisabled = false;
		return;
	}
}

void TCP_connection::ContinueReading()
{
	if (InputHandler::Instance().hasConnection)
	{
		try
		{
			socket().async_read_some(
				boost::asio::buffer(Messenger::Instance().recievedMessage),
				boost::bind(&TCP_connection::handle_read, shared_from_this(),
					boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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
	try
	{
		socket().async_read_some(
			boost::asio::buffer(Messenger::Instance().recievedMessage),
			boost::bind(&TCP_connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	catch (std::exception &ex)
	{
		std::cout << "Client disconnected" << std::endl;
		InputHandler::Instance().hasConnection = false;
		InputHandler::Instance().isCurrentComputerDisabled = false;
		return;
	}
	while (InputHandler::Instance().hasConnection /*&& !InputHandler::Instance().isCurrentComputerDisabled*/)
	{
		if (!Messenger::Instance().sentMessages.empty())
		{
			try
			{
				boost::asio::write(socket(),
					boost::asio::buffer(Messenger::Instance().sentMessages.front()));
				Messenger::Instance().sentMessages.pop();
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

void TCP_connection::SetConnections()
{
	boost::asio::ip::tcp::no_delay noDelayOption(true);
	socket_.set_option(noDelayOption);
	if (!Messenger::Instance().sentMessages.empty())
	{
		try
		{
			boost::asio::write(socket(),
				boost::asio::buffer(Messenger::Instance().sentMessages.front()));
			Messenger::Instance().sentMessages.pop();
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
