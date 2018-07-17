#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	static InputHandler handler;
	return handler;
}
LRESULT CALLBACK KeyboardEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *hooked_key = (KBDLLHOOKSTRUCT*)lParam;
	if (hooked_key != NULL)
	{
		std::string wparam = std::to_string(wParam);
		std::string lparam = std::to_string(lParam);
		std::string kcode = std::to_string(hooked_key->vkCode);
		std::string message = "0 " + wparam + ' ' + lparam + ' ' + kcode + '\0';
		if (InputHandler::Instance().hasConnection)
		{
			InputHandler::Instance().sentMessage.push(message);
		}
		return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

bool MouseEventProcOutOfBorder(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		POINT P;
		GetCursorPos(&P);
		float yCoord, xCoord;
		if (pMouseStruct->pt.x < 0 && P.x == 0 && !InputHandler::Instance().isCurrentComputerDisabled)
		{
			InputHandler::Instance().isCurrentComputerDisabled = true;
			yCoord = (float)P.y / GetSystemMetrics(SM_CYSCREEN);
			InputHandler::Instance().sentMessage.push("2 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			return true;
		}
		if (pMouseStruct->pt.x > 0 && P.x == GetSystemMetrics(SM_CXSCREEN) - 1 && !InputHandler::Instance().isCurrentComputerDisabled)
		{
			InputHandler::Instance().isCurrentComputerDisabled = true;
			yCoord = (float)P.y / GetSystemMetrics(SM_CYSCREEN);
			InputHandler::Instance().sentMessage.push("3 " + std::to_string(yCoord));
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			return true;
		}
	}
	return false;
}
LRESULT CALLBACK MouseEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		if (InputHandler::Instance().hasConnection)
		{
			if (!MouseEventProcOutOfBorder(nCode, wParam, lParam))
			{
				std::string wparam = std::to_string(wParam);
				std::string lparam = std::to_string(lParam);
				short dx = pMouseStruct->pt.x - InputHandler::Instance().mousePosition.x;
				short dy = pMouseStruct->pt.y - InputHandler::Instance().mousePosition.y;
				std::string delta = std::to_string(dx) + ' ' + std::to_string(dy);
				std::string message = "1 " + wparam + ' ' + lparam + ' ' + delta + '\0';
				if (InputHandler::Instance().hasConnection)
				{
					InputHandler::Instance().sentMessage.push(message);
				}
				GetCursorPos(&InputHandler::Instance().mousePosition);
			}
		}
		return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

void InputHandler::MyMouseLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEventProcServer, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

}

void InputHandler::MyKeyboardLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEventProcServer, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);

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

void InputHandler::Run()
{
}