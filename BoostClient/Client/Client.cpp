#include "stdafx.h"
#include <boost/asio.hpp>
#include <iostream>
#include <vector> 
using  boost::asio::ip::tcp;


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