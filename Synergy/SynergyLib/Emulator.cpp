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

void Emulator::ParseMSG(std::string strRecvMessage)
{
	std::istringstream iss;
	iss.str(strRecvMessage);

	if (strRecvMessage[0] == '1')
	{
		std::string mouse[5] = { " " };
		for (size_t i = 0; i < 5; i++)
		{
			iss >> mouse[i];
		}
		int wval = atoi(mouse[1].c_str());
		int lval = atoi(mouse[2].c_str());

		short xval = (short)atoi(mouse[3].c_str());
		short yval = (short)atoi(mouse[4].c_str());

		Emulator::MouseMove(xval, yval);
		if (wval != MOUSEEVENTF_MOVE)
		{
			Emulator::MouseAction(wval);
		}

	}
	else if (strRecvMessage[0] == '0')
	{
		std::string code[4] = { " " };

		for (int i = 0; i < 4; i++)
		{
			iss >> code[i];
		}
		int wval = atoi(code[1].c_str());
		int lval = atoi(code[2].c_str());

		unsigned short val = (unsigned short)atoi(code[3].c_str());
		Emulator::KeyAction(val, wval);
	}
	else if (strRecvMessage[0] == '2')
	{
		std::string mouse[4] = { " " };
		for (size_t i = 0; i < 4; i++)
		{
			iss >> mouse[i];
		}
		int wval = atoi(mouse[1].c_str());
		int lval = atoi(mouse[2].c_str());

		DWORD delta = atoi(mouse[3].c_str());
		Emulator::MouseScroll(delta);
	}
	else if (strRecvMessage[0] == '3')
	{
		std::string mouse[2] = { " " };
		for (size_t i = 0; i < 2; i++)
		{
			iss >> mouse[i];
		}
		float wval = atof(mouse[1].c_str());
		int yval = wval * GetSystemMetrics(SM_CYSCREEN);
		InputHandler::Instance().isCurrentComputerDisabled = false;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = (GetSystemMetrics(SM_CXSCREEN) - 1)*(65536 / GetSystemMetrics(SM_CXSCREEN)); //x being coord in pixels
		input.mi.dy = yval * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		GetCursorPos(&InputHandler::Instance().mousePosition);
	}
	else if (strRecvMessage[0] == '4')
	{
		std::string mouse[2] = { " " };
		for (size_t i = 0; i < 2; i++)
		{
			iss >> mouse[i];
		}
		float wval = atof(mouse[1].c_str());
		int yval = wval * GetSystemMetrics(SM_CYSCREEN);
		InputHandler::Instance().isCurrentComputerDisabled = false;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 0;//x being coord in pixels
		input.mi.dy = yval * (65536 / GetSystemMetrics(SM_CYSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		GetCursorPos(&InputHandler::Instance().mousePosition);
	}
	else if (strRecvMessage[0] == '5')
	{
		std::string mouse[2] = { " " };
		for (size_t i = 0; i < 2; i++)
		{
			iss >> mouse[i];
		}
		float wval = atof(mouse[1].c_str());
		int yval = wval * GetSystemMetrics(SM_CXSCREEN);
		InputHandler::Instance().isCurrentComputerDisabled = false;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dy = (GetSystemMetrics(SM_CYSCREEN) - 1)*(65536 / GetSystemMetrics(SM_CYSCREEN)); //x being coord in pixels
		input.mi.dx = yval * (65536 / GetSystemMetrics(SM_CXSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		GetCursorPos(&InputHandler::Instance().mousePosition);
	}
	else if (strRecvMessage[0] == '6')
	{
		std::string mouse[2] = { " " };
		for (size_t i = 0; i < 2; i++)
		{
			iss >> mouse[i];
		}
		float wval = atof(mouse[1].c_str());
		int yval = wval * GetSystemMetrics(SM_CXSCREEN);
		InputHandler::Instance().isCurrentComputerDisabled = false;
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dy = 0;//x being coord in pixels
		input.mi.dx = yval * (65536 / GetSystemMetrics(SM_CXSCREEN)); //y being coord in pixels
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		GetCursorPos(&InputHandler::Instance().mousePosition);
	}
	else if (strRecvMessage[0] == '7')
	{
		std::string neighbours[5] = { "0" };
		for (size_t i = 0; i < 5; i++)
		{
			iss >> neighbours[i];
		}
		for (int i = 1; i < 5; i++)
		{
			InputHandler::Instance().neighbours[i - 1] = neighbours[i];
		}
	}
}