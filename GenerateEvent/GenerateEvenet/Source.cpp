#include <Windows.h>


// @brief Performing keyboard action
// @param vkey input key
// @param flag set of parameters which will define action
void KeyAction(WORD vkey, DWORD flag)
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


// @brief Performing mouse button action
// @param flag set of parameters which will define action
void MouseAction(DWORD flag)
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
void MouseMove(int dx, int dy)
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	POINT p;
	GetCursorPos(&p);
	input.mi.dx = dx * (65535.0f / GetSystemMetrics(SM_CXSCREEN)) + p.x * (65535.0f / GetSystemMetrics(SM_CXSCREEN));
	input.mi.dy = dy * (65535.0f / GetSystemMetrics(SM_CYSCREEN)) + p.y * (65535.0f / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	SendInput(1, &input, sizeof(input));
}

int main()
{
	system("pause");
	return 0;
}