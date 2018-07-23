#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "BoostServer.h"
#include "BoostClient.h"
#include "TCP_connection.h"
using namespace std;


static class ISynergy
{
	static int choice ;
	static string server_ip_adress;

public:
	ISynergy();
	~ISynergy();
	static void MainMenu();
	static void ServerMode();
	static void ClientMode();
	static void Paint(BoostServer &server);
	static void Position(TCP_connection::pointer new_connection, int &X, int &Y);
	static bool WaitConnect();

};

