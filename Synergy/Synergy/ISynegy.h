#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class ISynegy
{
private:
	int choice;
	vector<std::string> ip_adress;
public:
	ISynegy();
	~ISynegy();
	void MainMenu();
};

