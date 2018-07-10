#include "stdafx.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using  boost::asio::ip::tcp;


void ParseMSG(std::string Message,int& wParam, int& lParam , int& Keycode) 
{
	std::istringstream iss;
	iss.str(Message);
	int code[4] = { 0 };
	for (size_t i = 0; i < 4; i++)
	{
		iss >> code[i];
	}
	wParam = code[1];
	lParam = code[2];
	Keycode = code[3];
}

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::endpoint ep(boost::asio::ip::address::from_string("10.100.26.160"), 8080);
		std::cout << ep.address() << std::endl;
		tcp::socket socket(io_service);
		socket.connect(ep);
		if (socket.is_open())
		{
			std::cout << "connect!" << std::endl;
			boost::asio::streambuf boost_stream;
			std::string buf = "";
			socket.read_some(boost::asio::buffer(buf));
			std::cout << buf << std::endl;
		}
		system("pause");
		return 0;
	}
	catch (std::exception& e)
	{
		
		std::cout << e.what() << std::endl;
		system("pause");
	}
}