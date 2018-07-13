#include "BoostClient.h"

using boost::asio::ip::tcp;


const char SERVER_IP[] = "10.100.26.21";
const unsigned short PORT_NUMBER = 8080;
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);

//
//class TestClient
//{
//public:
//	TestClient(boost::asio::io_service& io_service)
//		: m_io_service(io_service),
//		m_Socket(io_service),
//		m_nSeqNumber(0)
//	{ 
//	}
//
//	void Connect(boost::asio::ip::tcp::endpoint& endpoint)
//	{
//		m_Socket.async_connect(endpoint,
//			boost::bind(&TestClient::handle_connect,
//				this,
//				boost::asio::placeholders::error));
//	}
//private:
//	void PostReceive()
//	{
//		
//		m_Socket.async_read_some(boost::asio::buffer(buff),
//			boost::bind(&TestClient::handle_receive, this,
//				boost::asio::placeholders::error,
//				boost::asio::placeholders::bytes_transferred));
//	}
//
//
//	void handle_connect(const boost::system::error_code& error)
//	{
//		if (error)
//		{
//			std::cout << "handle_connect connect failed error No: " << error.value() << " error Message: " << error.message() << std::endl;
//		}
//		else
//		{
//			std::cout << "connected" << std::endl; 
//			PostReceive();
//		}
//	}
//
//
//	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
//	{
//		if (error)
//		{
//			if (error == boost::asio::error::eof)
//			{
//				std::cout << "Disconnect" << std::endl;
//			}
//			else
//			{
//				std::cout << "handle_receive error No: " << error.value() << " error Message: " << error.message() << std::endl;
//			}
//		}
//		else
//		{
//			const std::string strRecvMessage = buff;
//			std::cout << "Message from server : " << strRecvMessage << std::endl;
//			PostReceive();
//		}
//	}
//
//
//
//	boost::asio::io_service& m_io_service;
//	boost::asio::ip::tcp::socket m_Socket;
//
//	int m_nSeqNumber;
//	char buff[1024];
//	std::string m_WriteMessage;
//};



int main()
{

	boost::asio::io_service io_service;


	BClient client(io_service);

	client.Connect(endpoint);
	boost::system::error_code ec;



	io_service.run(ec);
	if (ec)
		std::cout << "io_service error No: " << ec.value() << " error Message: " << ec.message() << std::endl;

	system("pause");
	return 0;
}



