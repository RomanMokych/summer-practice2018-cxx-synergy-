#pragma once
#pragma comment( lib, "user32.lib" )
#include "Messenger.h"
#include <stdio.h>
#include <thread>
#include <iostream>
#include <cstdlib>

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
	bool MouseEventProcOutOfBorder(LPARAM lParam);
	std::string neighbours[4] = { "0", "0", "0", "0" };
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