#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	static InputHandler handler;
	return handler;
}

LRESULT CALLBACK KeyboardEventProcClient(int nCode, WPARAM wParam, LPARAM lParam)
{
	return (InputHandler::Instance()isCurrentComputerDisabled.load() ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
}

LRESULT CALLBACK KeyboardEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *hooked_key = (KBDLLHOOKSTRUCT*)lParam;
	if (hooked_key != NULL)
	{
		std::string wparam = std::to_string(InputHandler::Instance().GetKeyBoardAction(wParam));
		std::string lparam = std::to_string(lParam);
		std::string kcode = std::to_string(hooked_key->vkCode);

		if (hooked_key->vkCode == VK_LCONTROL && 0x51) { 
			exit(0); 
		}
		if (wparam != "2")
		{
			std::string message = "0 " + wparam + ' ' + lparam + ' ' + kcode + '\0';
			if (InputHandler::Instance().hasConnection.load())
			{
				InputHandler::Instance().sentMessage.push(message);
			}
		}
		std::cout << InputHandler::Instance().isCurrentComputerDisabled.load() << std::endl;
		return (InputHandler::Instance().isCurrentComputerDisabled.load() ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}
LRESULT CALLBACK MouseEventProcClient(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		if (InputHandler::Instance().MouseEventProcOutOfBorder(nCode, wParam, lParam))
		{
			InputHandler::Instance().isCurrentComputerDisabled.store(true);
		}
	}
	return (InputHandler::Instance().isCurrentComputerDisabled.load() ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
}
LRESULT CALLBACK MouseEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		if (InputHandler::Instance().hasConnection.load())
		{
			if (!InputHandler::Instance().MouseEventProcOutOfBorder(nCode, wParam, lParam))
			{
				std::string wparam = std::to_string(wParam);
				std::string lparam = std::to_string(lParam);
				short dx = pMouseStruct->pt.x - InputHandler::Instance().mousePosition.x;
				short dy = pMouseStruct->pt.y - InputHandler::Instance().mousePosition.y;
				int action = InputHandler::Instance().GetMouseAction(wParam);
				std::string delta;
				std::string message;
				if (action != -1 && action != MOUSEEVENTF_WHEEL)
				{
					delta = std::to_string(dx) + ' ' + std::to_string(dy);
					message = "1 " + std::to_string(action) + ' ' + lparam + ' ' + delta + '\0';
				}
				else if (action == MOUSEEVENTF_WHEEL)
				{
					MSLLHOOKSTRUCT *pMhs = (MSLLHOOKSTRUCT *)lParam;
					short zDelta = HIWORD(pMhs->mouseData);
					zDelta /= 120;
					delta = std::to_string(zDelta) + ' ';
					message = "2 " + std::to_string(action) + ' ' + lparam + ' ' + delta + '\0';
				}
				if (InputHandler::Instance().hasConnection.load() && action != -1)
				{
					InputHandler::Instance().sentMessage.push(message);
				}
				GetCursorPos(&InputHandler::Instance().mousePosition);
			}
		}

		std::cout << InputHandler::Instance().isCurrentComputerDisabled.load() << std::endl;
		return (InputHandler::Instance().isCurrentComputerDisabled.load() ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

void InputHandler::ServerMouseLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEventProcServer, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

}

void InputHandler::ServerKeyboardLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEventProcServer, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);

}

void InputHandler::ClientKeyboardLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEventProcClient, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);
}

void InputHandler::ClientMouseLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEventProcClient, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

}

void InputHandler::MessageLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

int InputHandler::GetMouseAction(WPARAM wParam)
{
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		return MOUSEEVENTF_LEFTDOWN;
		break;
	case WM_LBUTTONUP:
		return MOUSEEVENTF_LEFTUP;
		break;
	case WM_MBUTTONDOWN:
		return MOUSEEVENTF_MIDDLEDOWN;
		break;
	case WM_MBUTTONUP:
		return MOUSEEVENTF_MIDDLEUP;
		break;
	case WM_RBUTTONDOWN:
		return MOUSEEVENTF_RIGHTDOWN;
		break;
	case WM_RBUTTONUP:
		return MOUSEEVENTF_RIGHTUP;
		break;
	case WM_XBUTTONDOWN:
		return MOUSEEVENTF_XDOWN;
		break;
	case WM_XBUTTONUP:
		return MOUSEEVENTF_XUP;
		break;
	case WM_MOUSEWHEEL:
		return MOUSEEVENTF_WHEEL;
		break;
	case WM_MOUSEMOVE:
		return MOUSEEVENTF_MOVE;
		break;
	default:
		return -1;
		break;
	}
}

int InputHandler::GetKeyBoardAction(WPARAM wParam)
{
	switch (wParam)
	{
	case WM_KEYDOWN:
		return 0;
	case WM_KEYUP:
		return KEYEVENTF_KEYUP;
	default:
		return -1;
		break;
	}
}

bool InputHandler::MouseEventProcOutOfBorder(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		POINT P;
		GetCursorPos(&P);
		float yCoord, xCoord;
		if (pMouseStruct->pt.x < 0 && P.x == 0 && !InputHandler::Instance().isCurrentComputerDisabled.load())
		{
			InputHandler::Instance().isCurrentComputerDisabled.store(true);
			yCoord = (float)P.y / GetSystemMetrics(SM_CYSCREEN);
			InputHandler::Instance().sentMessage.push("3 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			GetCursorPos(&InputHandler::Instance().mousePosition);
			return true;
		}
		if (pMouseStruct->pt.x > 0 && P.x == GetSystemMetrics(SM_CXSCREEN) - 1 && !InputHandler::Instance().isCurrentComputerDisabled.load())
		{
			InputHandler::Instance().isCurrentComputerDisabled.store(true);
			yCoord = (float)P.y / GetSystemMetrics(SM_CYSCREEN);
			InputHandler::Instance().sentMessage.push("4 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			GetCursorPos(&InputHandler::Instance().mousePosition);
			return true;
		}
		if (pMouseStruct->pt.y < 0 && P.y == 0 && !InputHandler::Instance().isCurrentComputerDisabled.load())
		{
			InputHandler::Instance().isCurrentComputerDisabled.store(true);
			yCoord = (float)P.x / GetSystemMetrics(SM_CXSCREEN);
			InputHandler::Instance().sentMessage.push("5 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			GetCursorPos(&InputHandler::Instance().mousePosition);
			return true;
		}
		if (pMouseStruct->pt.y > 0 && P.y == GetSystemMetrics(SM_CYSCREEN) - 1 && !InputHandler::Instance().isCurrentComputerDisabled.load())
		{
			InputHandler::Instance().isCurrentComputerDisabled.store(true);
			yCoord = (float)P.x / GetSystemMetrics(SM_CXSCREEN);
			InputHandler::Instance().sentMessage.push("6 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			GetCursorPos(&InputHandler::Instance().mousePosition);
			return true;
		}
		
	}
	return false;
}
