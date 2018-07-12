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
#include <bitset>

using boost::asio::ip::tcp;

class InputHandler
{
public:
	bool isCurrentComputerDisabled;
	HHOOK hKeyboardHook;
	HHOOK hMouseHook;
	POINT mousePosition;
	static InputHandler& Instance();
	void MyMouseLogger();
	void MyKeyboardLogger();
	void MessageLoop();
	void Run();
	std::string sentMessage;
};
LRESULT CALLBACK KeyboardEventProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam);