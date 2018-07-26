#include "Emulator.h"
#include "MessagesParser.h"

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
	input.mi.mouseData = delta;
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
	mouse_event(MOUSEEVENTF_MOVE | 0x2000, dx, dy, 0, 0);
}

void Emulator::MouseOutOfLeftBorder(float relation)
{
	InputHandler::Instance().isCurrentComputerDisabled = false;
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.dx = (GetSystemMetrics(SM_CXSCREEN) - 1)*(65536 / GetSystemMetrics(SM_CXSCREEN)); //x being coord in pixels
	input.mi.dy = (relation * GetSystemMetrics(SM_CXSCREEN)) * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	GetCursorPos(&InputHandler::Instance().mousePosition);
}

void Emulator::MouseOutOfRightBorder(float relation)
{
	InputHandler::Instance().isCurrentComputerDisabled = false;
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.dx = 0;//x being coord in pixels
	input.mi.dy = (relation * GetSystemMetrics(SM_CXSCREEN)) * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	GetCursorPos(&InputHandler::Instance().mousePosition);
}

void Emulator::MouseOutOfTopBorder(float relation)
{
	InputHandler::Instance().isCurrentComputerDisabled = false;
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.dy = (GetSystemMetrics(SM_CYSCREEN) - 1)*(65536 / GetSystemMetrics(SM_CYSCREEN)); //x being coord in pixels
	input.mi.dx = (relation * GetSystemMetrics(SM_CXSCREEN)) * (65536 / GetSystemMetrics(SM_CXSCREEN)); //y being coord in pixels
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	GetCursorPos(&InputHandler::Instance().mousePosition);
}

void Emulator::MouseOutOfBottomBorder(float relation)
{
	InputHandler::Instance().isCurrentComputerDisabled = false;
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.dy = 0;//x being coord in pixels
	input.mi.dx = (relation * GetSystemMetrics(SM_CXSCREEN)) * (65536 / GetSystemMetrics(SM_CXSCREEN)); //y being coord in pixels
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	GetCursorPos(&InputHandler::Instance().mousePosition);
}

void Emulator::ParseMSG(std::string strRecvMessage)
{
	switch (strRecvMessage[0])
	{
	case '0':
		{
			int key = 0, state = 0;
			MessagesParser::ParseKeyboardActionEvent(strRecvMessage, &key, &state);
			Emulator::KeyAction(key, state);
		}
		break;
	case '1': 
		{
			int x = 0, y = 0, action = 0;
			MessagesParser::ParseMouseEvent(strRecvMessage, &x, &y, &action);
			Emulator::MouseMove(x, y);
			if (action != MOUSEEVENTF_MOVE)
			{
				Emulator::MouseAction(action);
			}
		}
		break;
	case '2':
		Emulator::MouseScroll(MessagesParser::ParseMouseScrollEvent(strRecvMessage));
		break;
	case '3': 
		Emulator::MouseOutOfLeftBorder(MessagesParser::ParseBorderlineEvent(strRecvMessage));
		break;
	case '4':
		Emulator::MouseOutOfRightBorder(MessagesParser::ParseBorderlineEvent(strRecvMessage));
		break;
	case '5': 
		Emulator::MouseOutOfTopBorder(MessagesParser::ParseBorderlineEvent(strRecvMessage));
		break;
	case '6': 
		Emulator::MouseOutOfBottomBorder(MessagesParser::ParseBorderlineEvent(strRecvMessage));
		break;
	case '7': 
		MessagesParser::ParseNeighbours(strRecvMessage);
		break;
	default: 
		break;
	}
}