#include "BoostClient.h"

using boost::asio::ip::tcp;


const char SERVER_IP[] = "10.100.26.160";
const unsigned short PORT_NUMBER = 8080;
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);

int main()
{

	boost::asio::io_service io_service;


	BClient client(io_service);

	client.Connect(endpoint);
	boost::system::error_code ec;



	io_service.run(ec);
	if (ec)
		std::cout << "io_service error No: " << ec.value() << " error Message: " << ec.message() << std::endl;

	system("pause");
	return 0;
}



