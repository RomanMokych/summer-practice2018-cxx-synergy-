#pragma once
#include "stdafx.h"
#include <boost/asio.hpp>
#include <string>
#include <locale>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <bitset>
#include <boost/asio/read_until.hpp>
using  boost::asio::ip::tcp;

class BClient
{
public:
	BClient(boost::asio::io_service& io_service) :
		m_io_service(io_service),
		m_Socket(io_service),
		m_nSeqNumber(0);
	~BClient();
	
	void Connect(boost::asio::ip::tcp::endpoint& endpoint);
private:
	void PostReceive();
	void handle_connect(const boost::system::error_code& error);
	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);



	boost::asio::io_service& m_io_service;
	boost::asio::ip::tcp::socket m_Socket;

	int m_nSeqNumber;
	char buff[1024];
	std::string m_WriteMessage;

};

