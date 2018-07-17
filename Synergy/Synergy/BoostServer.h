#pragma once
#include "InputHandler.h"
#include "TCP_connection.h"

class BoostServer
{
private:
	tcp::acceptor acceptor_;
	void start_accept();
	void handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code& error);
public:
	BoostServer(boost::asio::io_service& io_service);
};

