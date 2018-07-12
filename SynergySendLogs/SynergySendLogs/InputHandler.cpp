#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	static InputHandler handler;
	return handler;
}

LRESULT CALLBACK KeyboardEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	DWORD SHIFT_key = 0;
	DWORD CTRL_key = 0;
	DWORD ALT_key = 0;
	KBDLLHOOKSTRUCT *hooked_key = (KBDLLHOOKSTRUCT*)lParam;
	if (hooked_key != NULL)
	{
		std::string wparam = std::bitset<sizeof(wParam) * 8>(wParam).to_string();
		std::string lparam = std::bitset<sizeof(lParam) * 8>(lParam).to_string();
		std::string kcode = std::bitset<sizeof(short) * 8>(hooked_key->vkCode).to_string();
		std::string message = "0 " + wparam + ' ' + lparam + ' ' + kcode + '\0';
		InputHandler::Instance().sentMessage = message;
		std::cout << message << std::endl;
		return CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam);
	}
}

LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		std::string wparam = std::bitset<sizeof(wParam) * 8>(wParam).to_string();
		std::string lparam = std::bitset<sizeof(lParam) * 8>(lParam).to_string();
		POINT newPosition;
		GetCursorPos(&newPosition);
		short dx = newPosition.x - InputHandler::Instance().mousePosition.x;
		short dy = newPosition.y - InputHandler::Instance().mousePosition.y;
		std::string delta = std::bitset<sizeof(dx) * 8>(dx).to_string() + ' ' + std::bitset<sizeof(dy) * 8>(dy).to_string();
		std::string message = "1 " + wparam + ' ' + lparam + ' ' + delta  + '\0';
		InputHandler::Instance().sentMessage = message;
		GetCursorPos(&InputHandler::Instance().mousePosition);
		std::cout << message << std::endl;

	}
	return CallNextHookEx(InputHandler::Instance().hMouseHook, nCode, wParam, lParam);
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
	try
	{
		GetCursorPos(&InputHandler::Instance().mousePosition);
		std::thread mouseThread(&InputHandler::MyMouseLogger, InputHandler::Instance());
		std::thread keyboardThread(&InputHandler::MyKeyboardLogger, InputHandler::Instance());

		mouseThread.join();
		keyboardThread.join();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}