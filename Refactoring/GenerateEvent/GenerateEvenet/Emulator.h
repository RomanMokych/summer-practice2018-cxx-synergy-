#pragma once
#include <Windows.h>
static class Emulator
{
public:
	static void KeyAction(WORD vkey, DWORD flag);
	static void MouseScroll(DWORD delta);
	static void MouseAction(DWORD flag);
	static void MouseMove(int dx, int dy);
};

