#include "BoostServer.h"
#include "TCP_connection.h"

void BoostServer::start_accept()
{
	TCP_connection::pointer new_connection =
		TCP_connection::create(acceptor_.get_io_service());
	
	/*if (new_connection.use_count() != 0) {
		connections.insert(std::pair<std::string, TCP_connection::pointer>(new_connection->socket().remote_endpoint().address().to_string(), new_connection));
		std::cout << connections.find(new_connection->socket().remote_endpoint().address().to_string())->first << std::endl;
	}*/

	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&BoostServer::handle_accept, this, new_connection,
			boost::asio::placeholders::error));

}

void BoostServer::handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code & error)
{
	if (!error)
	{
		try
		{
			connections.insert(std::pair<std::string, std::shared_ptr<TCP_connection>>(new_connection->socket().remote_endpoint().address().to_string(), new_connection));
			for (auto it = connections.cbegin(); it != connections.cend(); ++it)
			{
				std::cout << it->first << std::endl;
			}
		}
		catch (std::exception&ex)
		{
			std::cout << ex.what() << std::endl;
		}
		std::cout << "A client connected" << std::endl;
		std::thread(&TCP_connection::start, new_connection).detach();
	}

	start_accept();
}

BoostServer::BoostServer(boost::asio::io_service & io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8080))
{
	start_accept();
}
