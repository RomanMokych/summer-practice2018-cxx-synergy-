#pragma once
#include "InputHandler.h"
#include "TCP_connection.h"
#include <map>
<<<<<<< HEAD
=======

>>>>>>> 1c109795c164acf451a485c6f5dd566c35ac97da
class BoostServer
{
private:
	std::map<std::string, TCP_connection::pointer> connections;
	tcp::acceptor acceptor_;
	void start_accept();
	void handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code& error);
public:
	std::map<std::string, std::shared_ptr<TCP_connection>> connections;
	BoostServer(boost::asio::io_service& io_service);
};

