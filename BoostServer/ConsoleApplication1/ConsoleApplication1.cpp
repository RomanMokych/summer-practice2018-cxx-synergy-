#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>

using boost::asio::ip::tcp;
typedef  boost::shared_ptr<tcp::socket> socket_ptr;
void start_accept(socket_ptr sock);
void handle_accept(socket_ptr sock, const boost::system::error_code & err);

boost::asio::io_service io_service;
tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

int main()
{

	while (1)
	{
		socket_ptr sock(new boost::asio::ip::tcp::socket(io_service));
		start_accept(sock);
		io_service.run();
	}
}
void start_accept(socket_ptr sock)
{
	acceptor.async_accept(*sock, boost::bind(handle_accept, sock, _1));
}
void handle_accept(socket_ptr sock, const boost::system::error_code & err)
{
	if (err) return;
	// at this point, you can read/write to the socket
	std::cout << "connect!" << std::endl;
	std::string buf = "Hello , uyobok";
	std::cin >> buf;
	sock->write_some(boost::asio::buffer(buf));
	//std::cout << buf << std::endl;
	socket_ptr sockt(new boost::asio::ip::tcp::socket(io_service));
	start_accept(sockt);
}