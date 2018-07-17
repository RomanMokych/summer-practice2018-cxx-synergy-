#include "BoostClient.h"
#include "BoostServer.h"
#include <conio.h>


void Server() {
	try
	{
		InputHandler::Instance().hasConnection = InputHandler::Instance().isCurrentComputerDisabled = false;
		GetCursorPos(&InputHandler::Instance().mousePosition);
		std::thread mouseThread(&InputHandler::MyMouseLogger, InputHandler::Instance());
		std::thread keyboardThread(&InputHandler::MyKeyboardLogger, InputHandler::Instance());
		boost::asio::io_service io_service;
		BoostServer server(io_service);
		io_service.run();

		mouseThread.join();
		keyboardThread.join();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}





void Client() {
	//const char SERVER_IP[] = "10.100.26.160";
	const unsigned short PORT_NUMBER = 8080;
	std::string Server_IP = " ";
	std::cin >> Server_IP;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(Server_IP), PORT_NUMBER);


	boost::asio::io_service io_service;
	BClient client(io_service);
	client.Connect(endpoint);
	boost::system::error_code ec;
	io_service.run(ec);
	if (ec) std::cout << "io_service error No: " << ec.value() << " error Message: " << ec.message() << std::endl;

}


int main() {
	char choice;
	std::cout << "1 for server" << std::endl;
	std::cout << "2 for client" << std::endl;
	choice = _getch();
	switch (choice)
	{
	case '1':
		Server();
		break;
	case '2':
		Client();
		break;
	}
	system("pause");
	return 0;	
}