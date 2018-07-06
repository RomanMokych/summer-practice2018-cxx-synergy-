#pragma comment( lib, "user32.lib" )

#include <windows.h>
#include <stdio.h>

HHOOK hKeyboardHook;
HHOOK hMouseHook;

LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
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
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}


LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		// TO DO: Send wparam to define comand
		printf("Mouse position X = %d  Mouse Position Y = %d\n", pMouseStruct->pt.x, pMouseStruct->pt.y);
		// TO DO: Calc delta movement, send it

	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void MessageLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

DWORD WINAPI MyMouseLogger(LPVOID lpParm)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

	return 0;
}

DWORD WINAPI MyKeyboardLogger(LPVOID lpParm)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);

	return 0;
}

int main()
{
	HANDLE mutex;
	DWORD ThreadId;
	HANDLE Threads[2];
	mutex = CreateMutex(NULL, FALSE, NULL);
	if (mutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	Threads[0] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MyKeyboardLogger, 0, NULL, &ThreadId);
	if (Threads[0] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	}

	Threads[1] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MyMouseLogger, 0, NULL, &ThreadId);
	if (Threads[1] == NULL)
	{
		printf("CreateThread error: %d\n", GetLastError());
		return 1;
	}

	WaitForMultipleObjects(2, Threads, TRUE, INFINITE);

	for (int i = 0; i < 2; i++)
		CloseHandle(Threads[i]);

	CloseHandle(mutex);

	return 0;
}