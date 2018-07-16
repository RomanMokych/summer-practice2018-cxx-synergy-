#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	static InputHandler handler;
	return handler;
}

LRESULT CALLBACK KeyboardEventProc(int nCode, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL)
	{
		std::string wparam = std::to_string(wParam);
		std::string lparam = std::to_string(lParam);
		short dx = pMouseStruct->pt.x - InputHandler::Instance().mousePosition.x;
		short dy = pMouseStruct->pt.y - InputHandler::Instance().mousePosition.y;
		std::string delta = std::to_string(dx) + ' ' + std::to_string(dy);
		std::string message = "1 " + wparam + ' ' + lparam + ' ' + delta  + '\0';
		if (InputHandler::Instance().hasConnection)
		{
			InputHandler::Instance().sentMessage.push(message);
		}
		GetCursorPos(&InputHandler::Instance().mousePosition);
		return (InputHandler::Instance().isCurrentComputerDisabled ? 1 : CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam));
	}
}

void InputHandler::MyMouseLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEventProc, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

}

void InputHandler::MyKeyboardLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEventProc, hInstance, NULL);
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