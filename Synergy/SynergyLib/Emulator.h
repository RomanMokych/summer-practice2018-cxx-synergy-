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

	static void MouseOutOfLeftBorder(float relation);
	static void MouseOutOfRightBorder(float relation);
	static void MouseOutOfTopBorder(float relation);
	static void MouseOutOfBottomBorder(float relation);

	static void ParseMSG(std::string strRecvMessage);
};

