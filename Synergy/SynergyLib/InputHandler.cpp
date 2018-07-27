#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	std::unique_lock <std::mutex> un(mutex_);
	static InputHandler handler;
	return handler;
}
LRESULT CALLBACK KeyboardEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *hooked_key = (KBDLLHOOKSTRUCT*)lParam;
	if (hooked_key != NULL)
	{
		if (InputHandler::Instance().hasConnection /*&& (wParam != WM_KEYUP)*/)
		{
			Messenger::Instance().AddKeyboardMessage(wParam, lParam, hooked_key->vkCode);
		}
		return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

LRESULT CALLBACK MouseEventProcServer(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		if (InputHandler::Instance().hasConnection)
		{
			if (!InputHandler::Instance().MouseEventProcOutOfBorder(lParam))
			{
				
				if (InputHandler::Instance().hasConnection)
				{
					Messenger::Instance().AddMouseMessage(wParam, lParam, InputHandler::Instance().mousePosition);
				}
				GetCursorPos(&InputHandler::Instance().mousePosition);
			}
		}
		return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

LRESULT CALLBACK KeyboardEventProcClient(int nCode, WPARAM wParam, LPARAM lParam)
{
	return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
}

LRESULT CALLBACK MouseEventProcClient(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		if (InputHandler::Instance().hasConnection)
		{
			if (InputHandler::Instance().MouseEventProcOutOfBorder(lParam));
			else
			{
				GetCursorPos(&InputHandler::Instance().mousePosition);
			}
		}
	}
	return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
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

bool InputHandler::MouseEventProcOutOfBorder(LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		bool monitorDeactivated = MouseMoveEventToBorderEvent(pMouseStruct->pt, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		if (monitorDeactivated)
		{
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			GetCursorPos(&mousePosition);
		}

		return monitorDeactivated;
	}
	return false;
}

bool InputHandler::MouseMoveEventToBorderEvent(const POINT& currentMousePosition, int screenWidth, int screenHeight)
{
	if (!isCurrentComputerDisabled )
	{
		if (currentMousePosition.x - mousePosition.x < 0 &&
			mousePosition.x == 0 &&
			neighbours[3] != "0")
		{
			isCurrentComputerDisabled = true;
			Messenger::Instance().AddOutOfBorderMessage("3 ", (float)currentMousePosition.y / screenHeight);
			return true;
		}
		if (currentMousePosition.x - mousePosition.x > 0 &&
			mousePosition.x == screenWidth - 1 &&
			neighbours[1] != "0")
		{
			isCurrentComputerDisabled = true;
			Messenger::Instance().AddOutOfBorderMessage("4 ", (float)currentMousePosition.y / screenHeight);
			return true;
		}
		if (currentMousePosition.y - mousePosition.y < 0 &&
			mousePosition.y == 0 &&
			neighbours[0] != "0")
		{
			isCurrentComputerDisabled = true;
			Messenger::Instance().AddOutOfBorderMessage("5 ", (float)currentMousePosition.x / screenWidth);
			return true;
		}
		if (currentMousePosition.y - mousePosition.y > 0 &&
			mousePosition.y == screenHeight - 1 &&
			neighbours[2] != "0")
		{
			isCurrentComputerDisabled = true;
			Messenger::Instance().AddOutOfBorderMessage("6 ", (float)currentMousePosition.x / screenWidth);
			return true;
		}
	}
	return false;
}

std::mutex InputHandler::mutex_;