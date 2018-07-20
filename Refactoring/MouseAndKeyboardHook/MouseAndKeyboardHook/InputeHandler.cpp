#include "InputeHandler.h"


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

	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
		DWORD dwMsg = 1;
		dwMsg += hooked_key.scanCode << 16;
		dwMsg += hooked_key.flags << 24;
		char lpszKeyName[1024] = { 0 };


		int key = hooked_key.vkCode;

		// TO DO SEND: key and command


		SHIFT_key = GetAsyncKeyState(VK_SHIFT);
		CTRL_key = GetAsyncKeyState(VK_CONTROL);
		ALT_key = GetAsyncKeyState(VK_MENU);

		printf("Keycode = %c\n", key);

		if (key >= 'A' && key <= 'Z')
		{

			if (GetAsyncKeyState(VK_SHIFT) >= 0) key += 32;

			SHIFT_key = 0;
			CTRL_key = 0;
			ALT_key = 0;
		}
	}
	return CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		// TO DO: Send wparam to define comand
		printf("Mouse position X = %d  Mouse Position Y = %d\n", pMouseStruct->pt.x, pMouseStruct->pt.y);
		// TO DO: Calc delta movement, send it

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
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void InputHandler::Run()
{
	try
	{
		std::thread mouseThread(&InputHandler::MyMouseLogger, InputHandler::Instance());
		std::thread keyboardThread(&InputHandler::MyKeyboardLogger, InputHandler::Instance());

		mouseThread.detach();
		keyboardThread.detach();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
