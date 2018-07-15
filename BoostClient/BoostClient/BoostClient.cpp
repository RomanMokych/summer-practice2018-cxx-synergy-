#include "BoostClient.h"

BClient::BClient(boost::asio::io_service& io_service) : m_Socket(io_service)
{
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
		strRecvMessage = buff;
		ParseMSG();
		std::cout << "Message from server : " << strRecvMessage << std::endl;
		PostReceive();
	}
}

void BClient::ParseMSG()
{
	std::istringstream iss;
	iss.str(strRecvMessage);

	if (strRecvMessage[0] == '1')
	{
		std::string mouse[5] = { " " };
		for (size_t i = 0; i < 5; i++)
		{
			iss >> mouse[i];
		}
		std::bitset<32> wparbits(mouse[1]);
		int wval = wparbits.to_ulong();

		std::bitset<32> lparbits(mouse[2]);
		int lval = lparbits.to_ulong();

		std::bitset<16> xbits(mouse[3]);
		short xval = (short)xbits.to_ulong();
		std::cout << xval << std::endl;

		std::bitset<16> ybits(mouse[4]);
		short yval = (short)ybits.to_ulong();
		std::cout << yval << std::endl;

	}
	else
	{
		std::string code[4] = { " " };

		for (int i = 0; i < 4; i++)
		{
			iss >> code[i];
		}
		std::bitset<32> wparbits(code[1]);
		int wval = wparbits.to_ulong();

		std::bitset<32> lparbits(code[2]);
		int lval = lparbits.to_ulong();

		std::bitset<16> kbits(code[3]);
		unsigned short val = kbits.to_ulong();
		Emulator::KeyAction(val, (WPARAM)(DWORD)wval);
	}
}

