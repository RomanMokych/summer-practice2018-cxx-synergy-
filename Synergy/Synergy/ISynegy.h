#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "BoostServer.h"
#include "BoostClient.h"
#include "TCP_connection.h"
using namespace std;


class ISynergy
{
	unsigned port_number;
	int choice;
	string server_ip_adress;
public:
	ISynergy();
	~ISynergy();
	void MainMenu();
	void ServerMode();
	void ClientMode();

};

