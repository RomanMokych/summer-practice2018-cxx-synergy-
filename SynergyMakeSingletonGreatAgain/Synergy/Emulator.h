#pragma once

#include <sstream>
#include "InputHandler.h"


static class Emulator
{
public:
	static void KeyAction(WORD vkey, DWORD flag);
	static void MouseScroll(DWORD delta);
	static void MouseAction(DWORD flag);
	static void MouseMove(int dx, int dy);
	static void ParseMSG(std::string strRecvMessage);
};

