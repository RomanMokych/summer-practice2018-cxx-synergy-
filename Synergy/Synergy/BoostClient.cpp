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
		std::cout << "Message from server : " << strRecvMessage<< std::endl;
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
		int wval = atoi(mouse[1].c_str());

		int lval = atoi(mouse[2].c_str());

		short xval = (short)atoi(mouse[3].c_str());
		//short xval = (short)xbits.to_ulong();
		//std::cout << xval << std::endl;

		short yval = (short)atoi(mouse[4].c_str());
		//short yval = (short)ybits.to_ulong();
		//std::cout << yval << std::endl;

		//Emulator::MouseMove(xval,yval);
		//Emulator::MouseAction(wval);

	}
	else
	{
		std::string code[4] = { " " };

		for (int i = 0; i < 4; i++)
		{
			iss >> code[i];
		}
		int wval = atoi(code[1].c_str());

		if (wval == 257)
		{
			return;
		}

		int lval = atoi(code[2].c_str());

		unsigned short val = (unsigned short)atoi(code[3].c_str());
		Emulator::KeyAction(val, (WPARAM)(DWORD)lval);
	
	}
}

