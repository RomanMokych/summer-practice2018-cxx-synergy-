#pragma once
#pragma comment( lib, "user32.lib" )

#include <windows.h>
#include <stdio.h>
#include <thread>
#include <iostream>

class InputHandler
{
public:
	HHOOK hKeyboardHook;
	HHOOK hMouseHook;
	static InputHandler& Instance();
	void MyMouseLogger();
	void MyKeyboardLogger();
	void MessageLoop();
	void Run();
};
LRESULT CALLBACK KeyboardEventProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam);