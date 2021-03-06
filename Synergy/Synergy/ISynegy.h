#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "..\SynergyLib\InputHandler.h"
#include "..\SynergyLib\BoostServer.h"
#include "..\SynergyLib\BoostClient.h"
#include "..\SynergyLib\Emulator.h"

using namespace std;


static class Synergy
{
	static int choice ;
	static string server_ip_adress;

public:
	Synergy();
	~Synergy();
	static void MainMenu();
	static void ServerMode();
	static void ClientMode();

};

