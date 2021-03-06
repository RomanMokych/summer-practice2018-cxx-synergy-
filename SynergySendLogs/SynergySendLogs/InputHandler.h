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
	bool isCurrentComputerDisabled;
	bool hasConnection;
	HHOOK hKeyboardHook;
	HHOOK hMouseHook;
	POINT mousePosition;
	static InputHandler& Instance();
	void ServerMouseLogger();
	void ServerKeyboardLogger();
	void ClientKeyboardLogger();
	void ClientMouseLogger();
	void MessageLoop();
	int GetMouseAction(WPARAM wParam);
	int GetKeyBoardAction(WPARAM wParam);
	bool MouseEventProcOutOfBorder(LPARAM lParam);
	std::queue<std::string> sentMessage;
	char recievedMessage[1024];
private:
	static std::mutex mutex_;
	InputHandler()
	{
		GetCursorPos(&mousePosition);
	}
	~InputHandler(){}
	InputHandler(InputHandler const&) = delete;
	InputHandler(InputHandler const&&) = delete;
	InputHandler operator=(InputHandler const&) = delete;
	InputHandler operator=(InputHandler const&&) = delete;
};