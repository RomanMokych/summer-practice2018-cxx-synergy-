#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;


class ISynergy
{
	unsigned port_number;
	int choice;
	vector<std::string> ip_adress;
	string server_ip_adress;
public:
	ISynergy();
	~ISynergy();
	void MainMenu();
	void ServerMode();
	void ClientMode();

};

