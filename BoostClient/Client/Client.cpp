#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using  boost::asio::ip::tcp;



int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::endpoint ep(boost::asio::ip::address::from_string("10.100.26.160"), 1234);
		std::cout << ep.address() << std::endl;
		tcp::socket socket(io_service);
		socket.connect(ep);
		if (socket.is_open())
		{
			std::cout << "connect!" << std::endl;
			boost::asio::streambuf boost_stream;
			std::string data = "Hello";
			socket.write_some(boost::asio::buffer(data));
		}
		system("pause");
		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}