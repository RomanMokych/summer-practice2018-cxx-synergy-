#include "Emulator.h"


// @brief Performing keyboard action
// @param vkey input key
// @param flag set of parameters which will define action
void Emulator::KeyAction(WORD vkey, DWORD flag)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = flag;
	SendInput(1, &input, sizeof(INPUT));
}

// @brief Performing mouse scrolling
// @param delta value of scrolling
void Emulator::MouseScroll(DWORD delta)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;
	input.mi.mouseData = delta * 120;
	SendInput(1, &input, sizeof(input));
}

// @brief Performing mouse button action
// @param flag set of parameters which will define action
void Emulator::MouseAction(DWORD flag)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;
	input.mi.dwFlags = flag;
	SendInput(1, &input, sizeof(INPUT));
}

// @brief Move cursor relatively its current position
// @param dx, dy - coordinates of changing position 
void Emulator::MouseMove(int dx, int dy)
{
	mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_MOVE_NOCOALESCE, dx, dy, 0, 0);
}
