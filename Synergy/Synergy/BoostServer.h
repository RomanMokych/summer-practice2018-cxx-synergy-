#pragma once
#include "InputHandler.h"
#include "TCP_connection.h"
#include <map>
class BoostServer
{
private:
	std::map<std::string, TCP_connection::pointer> connections;
	tcp::acceptor acceptor_;
	void start_accept();
	void handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code& error);
public:
	BoostServer(boost::asio::io_service& io_service);
};

