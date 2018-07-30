#include "BoostServer.h"
#include "TCP_connection.h"



void BoostServer::start_accept()
{
	TCP_connection::pointer new_connection =
		TCP_connection::create(acceptor_.get_io_service());
	
	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&BoostServer::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
}

void BoostServer::handle_accept(TCP_connection::pointer new_connection, const boost::system::error_code & error)
{
	int x, y;
	if (!error)
	{
		try
		{
			do
			{
				Position(new_connection, x, y);
				
			} while (connections.find(std::make_pair(x, y)) != connections.end());		
			connections.insert(std::pair <std::pair<int, int>, std::shared_ptr<TCP_connection >>(std::make_pair(x, y), new_connection));
			std::cout << connections.find(std::make_pair(x, y))->first.first << " " << connections.find(std::make_pair(x, y))->first.second << std::endl;
		}
		catch (std::exception&ex)
		{
			std::cout << ex.what() << std::endl;
		}
		if (WaitConnect())
		{
			start_accept();
		}
		else
		{
			// TODO make proper indexes
			for (auto iter = connections.begin(); iter != connections.end(); iter++)
			{
				std::string message = "7 0 0 0 0";
				if (connections.find(std::make_pair(iter->first.first, iter->first.second - 1)) != connections.end())
				{
					message[6] = '1';
				}
				else
				{
					if (std::make_pair(iter->first.first, iter->first.second - 1) == std::make_pair(0, 0))
					{
						InputHandler::Instance().neighbours[0] = "1";
						message[6] = '1';
					}
				}
				if (connections.find(std::make_pair(iter->first.first + 1, iter->first.second)) != connections.end())
				{
					message[4] = '1';
				}
				else
				{
					if (std::make_pair(iter->first.first + 1, iter->first.second) == std::make_pair(0, 0))
					{
						InputHandler::Instance().neighbours[3] = "1";
						message[4] = '1';
					}
				}
				if (connections.find(std::make_pair(iter->first.first, iter->first.second + 1)) != connections.end())
				{
					message[2] = '1';
				}
				else
				{
					if (std::make_pair(iter->first.first, iter->first.second + 1) == std::make_pair(0, 0))
					{
						InputHandler::Instance().neighbours[2] = "1";
						message[2] = '1';
					}
				}
				if (connections.find(std::make_pair(iter->first.first - 1, iter->first.second)) != connections.end())
				{
					message[8] = '1';
				}
				else
				{
					if (std::make_pair(iter->first.first - 1, iter->first.second) == std::make_pair(0, 0))
					{
						InputHandler::Instance().neighbours[1] = "1";
						message[8] = '1';
					}
				}
				std::cout << message << std::endl;
				Messenger::Instance().sentMessages.push(message);
				iter->second->SetConnections();
			}
			std::thread(&TCP_connection::start, new_connection).detach();
		}
	}
	start_accept();
}

BoostServer::BoostServer(boost::asio::io_service & io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8080))
{

	cords.first = 0;
	cords.second = 0;

	start_accept();
}


void BoostServer::Position(TCP_connection::pointer new_connection, int &X, int &Y)
{

	do
	{
		system("cls");
		std::cout << "Client " << new_connection->socket().remote_endpoint().address().to_string() << " connected. Set position(X;Y) : ";
		std::cin.clear();
		std::cin >> X >> Y;
	} while (!((X||Y) && (std::cin.good())));

}

bool BoostServer::WaitConnect()
{
	char answer;
	do
	{
		std::cout << "Do you want to connect a new client ? (1 - yes ; 0 - no) " << std::endl;

		std::cin >> answer;
		if (answer == '1') {
			return true;
		}
		else if (answer == '0') {
			return false;
		}
		else {
			std::cin.clear();
		}
	} while (true);
}