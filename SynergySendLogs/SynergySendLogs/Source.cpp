#include "InputHandler.h"
#include "BoostServer.h"

int main()
{
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
	return 0;
}