#include "ISynergy.h"



ISynergy::ISynergy()
{
	port_number = 8080;
}


ISynergy::~ISynergy()
{
}

void ISynergy::MainMenu() {
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
		exit(1);
	}

}

void ISynergy::ServerMode() {
	cout << "Server mode :" << endl;

	do
	{
		cout << "Waiting for connections ..." << endl;

	} while (choice != );


}
void ISynergy::ClientMode() {
	cout << "Client mode : " << endl;
	cout << "Set IP-adress of the server : ";
	cin >> server_ip_adress;
}
