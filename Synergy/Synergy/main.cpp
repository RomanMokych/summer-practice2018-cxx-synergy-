#include "BoostClient.h"
#include "BoostServer.h"
#include <conio.h>
#include "ISynegy.h"

void Server() {
	try
	{
		InputHandler::Instance().hasConnection = false;
		InputHandler::Instance().isCurrentComputerDisabled = false;
		GetCursorPos(&InputHandler::Instance().mousePosition);
		std::thread mouseThread(&InputHandler::ServerMouseLogger, std::ref(InputHandler::Instance()));
		std::thread keyboardThread(&InputHandler::ServerKeyboardLogger, std::ref(InputHandler::Instance()));
		boost::asio::io_service io_service;
		BoostServer server(io_service);
		std::thread serverThread([&] { io_service.run(); });

		mouseThread.detach();
		keyboardThread.detach();
		serverThread.join();
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
	std::thread mouseThread(&InputHandler::ClientMouseLogger, std::ref(InputHandler::Instance()));
	std::thread keyboardThread(&InputHandler::ClientKeyboardLogger, std::ref(InputHandler::Instance()));

	boost::asio::io_service io_service;
	BClient client(io_service);
	client.Connect(endpoint);
	boost::system::error_code ec;
	io_service.run(ec);

	mouseThread.join();
	keyboardThread.join();
	if (ec) std::cout << "io_service error No: " << ec.value() << " error Message: " << ec.message() << std::endl;

}


int main() {
	ISynergy ui  = ISynergy();
	ui.MainMenu();
	system("pause");
	return 0;	
}