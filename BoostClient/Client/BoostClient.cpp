#include "BoostClient.h"

BoostClient::BoostClient(boost::asio::io_service& io_service)
{
}

BoostClient::~BoostClient()
{
}
void BoostClient::PostReceive()
{

	m_Socket.async_read_some(boost::asio::buffer(buff),
		boost::bind(&BoostClient::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}


void BoostClient::handle_connect(const boost::system::error_code& error)
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


void BoostClient::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
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