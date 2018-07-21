#pragma once
#include "stdafx.h"
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <boost/bind.hpp>

using  boost::asio::ip::tcp;

class BClient
{
public:
	BClient(boost::asio::io_service& io_service);
	~BClient();
	
	void Connect(boost::asio::ip::tcp::endpoint& endpoint);
private:
	void PostReceive();
	void handle_connect(const boost::system::error_code& error);
	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);
	void handle_write();
	RECT getSysMonitor();
	std::string data_compression(int length);


	//Connection
	boost::asio::ip::tcp::socket m_Socket;
	
	
	//IO
	char buff[1024];
	std::string m_WriteMessage;

};

