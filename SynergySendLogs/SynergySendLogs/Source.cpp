#include "InputHandler.h"
#include "BoostServer.h"

int main()
{
	try
	{
		std::thread InputThread(&InputHandler::Run, InputHandler::Instance());
		boost::asio::io_service io_service;
		BoostServer server(io_service);
		io_service.run();

		InputThread.join();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}