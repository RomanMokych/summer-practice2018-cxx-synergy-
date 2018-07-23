#pragma once
#include "InputHandler.h"
#include "TCP_connection.h"
#include <map>


class BoostServer
{
private:
	tcp::acceptor acceptor_;
	void start_accept();
	void handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code& error);
public:
	int Xmax, Xmin, Ymax, Ymin;
	std::pair<int, int> cords;
	std::map<std::pair<int,int>, std::shared_ptr<TCP_connection>> connections;
	BoostServer(boost::asio::io_service& io_service);

};

