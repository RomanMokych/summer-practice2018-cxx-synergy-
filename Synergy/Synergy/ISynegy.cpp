#include "ISynegy.h"



Synergy::Synergy()
{
}


Synergy::~Synergy()
{
}


void Synergy::MainMenu() {

	cout << "Welcome to Synergy!" << endl;
	cout << "Set the role in the session :" << endl;
	cout << "1 - for Server ;" << endl;
	cout << "2 - for Client ;" << endl;
	cin >> choice;
	system("cls");
	if (choice == 1) {
		ServerMode();
	}
	else if (choice == 2) {
		ClientMode();
	}
	else {
		cerr << "Wrong input " << endl;
		system("pause");
		exit(1);
	}

}

void Synergy::ServerMode() {
	cout << "Server mode :" << endl;
	try
	{
		InputHandler::Instance().hasConnection = false;
		InputHandler::Instance().isCurrentComputerDisabled = false;
		GetCursorPos(&InputHandler::Instance().mousePosition);
		std::thread mouseThread(&InputHandler::ServerMouseLogger, std::ref(InputHandler::Instance()));
		std::thread keyboardThread(&InputHandler::ServerKeyboardLogger, std::ref(InputHandler::Instance()));
		boost::asio::io_service io_service;
		BoostServer server(io_service);
		
		FreeConsole();
		io_service.run();
		mouseThread.join();
		keyboardThread.join();
	}
	catch (const std::exception &ex)
	{
		std::cout << "Somethnig went wrong ."<< std::endl;
	}


}
void Synergy::ClientMode() {
	boost::system::error_code er;

	cout << "Client mode : " << endl;
	do
	{
		cout << "Set IP-adress of the server : ";
		cin >> server_ip_adress;
		boost::asio::ip::address::from_string(server_ip_adress, er);
	} while (er);
	
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(server_ip_adress), 8080);
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




int Synergy::choice = 10;
string Synergy::server_ip_adress = " ";

