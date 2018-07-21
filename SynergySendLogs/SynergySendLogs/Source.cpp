#include "InputHandler.h"
#include "BoostServer.h"

void Server()
{
	try
	{
		InputHandler::Instance().hasConnection = false;
		InputHandler::Instance().isCurrentComputerDisabled = false;
		std::thread mouseThread(&InputHandler::ServerMouseLogger, std::ref(InputHandler::Instance()));
		std::thread keyboardThread(&InputHandler::ServerKeyboardLogger, std::ref(InputHandler::Instance()));
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
int main()
{
	Server();
	return 0;
}