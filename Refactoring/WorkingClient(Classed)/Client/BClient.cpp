#include "stdafx.h"
#include "BClient.h"


BClient::BClient(boost::asio::io_service& io_service) : m_Socket(io_service)
{
	getSysMonitor();
}


BClient::~BClient()
{
}

void BClient::Connect(boost::asio::ip::tcp::endpoint& endpoint)
{
	m_Socket.async_connect(endpoint,
		boost::bind(&BClient::handle_connect,
			this,
			boost::asio::placeholders::error));
}

void BClient::PostReceive()
	{
		m_Socket.async_read_some(boost::asio::buffer(buff),
			boost::bind(&BClient::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}


void BClient::handle_connect(const boost::system::error_code& error)
	{
		if (error)
		{
			std::cout << "handle_connect connect failed error No: " << error.value() << " error Message: " << error.message() << std::endl;
		}
		else
		{
			std::cout << "connected" << std::endl;
			PostReceive();
		}
	}


void BClient::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				std::cout << "Disconnect" << std::endl;
			}
			else
			{
				std::cout << "handle_receive error No: " << error.value() << " error Message: " << error.message() << std::endl;
			}
		}
		else
		{
			const std::string strRecvMessage = buff;
			std::cout << "Message from server : " << strRecvMessage << std::endl;
			PostReceive();
		}
	}

void BClient::handle_write()
{
	boost::asio::write(m_Socket, boost::asio::buffer(buff));
}
RECT BClient::getSysMonitor() {
	RECT DesktopRect;
	HWND hDesktop = ::GetDesktopWindow();
	GetWindowRect(hDesktop, &DesktopRect);
	return DesktopRect;
}

std::string BClient::data_compression(int length) 
{
		if()
	return "hi";
}


