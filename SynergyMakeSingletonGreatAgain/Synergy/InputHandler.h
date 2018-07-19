#pragma once
#pragma comment( lib, "user32.lib" )

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <windows.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <atomic>

using boost::asio::ip::tcp;

class InputHandler
{
public:
	std::atomic_bool hasConnection;
	std::atomic_bool isCurrentComputerDisabled;
	HHOOK hKeyboardHook;
	HHOOK hMouseHook;
	POINT mousePosition;
	std::atomic <InputHandler> Instance();
	void ServerMouseLogger();
	void ServerKeyboardLogger();
	void ClientKeyboardLogger();
	void ClientMouseLogger();
	void MessageLoop();
	int GetMouseAction(WPARAM wParam);
	int GetKeyBoardAction(WPARAM wParam);
	bool MouseEventProcOutOfBorder(int nCode, WPARAM wParam, LPARAM lParam);
	std::queue<std::string> sentMessage;
	char recievedMessage[1024];
private:
	InputHandler() {}
	~InputHandler() {}
};