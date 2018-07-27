#include "Messenger.h"



Messenger & Messenger::Instance()
{
	std::unique_lock <std::mutex> unique(mutex_);
	static Messenger instance;
	return instance;
}

void Messenger::AddKeyboardMessage(WPARAM wParam, const int& vkCode)
{
	std::string action = std::to_string(GetKeyBoardAction(wParam));
	std::string kcode = std::to_string(vkCode);
	std::string message = "0 " + action + ' ' + kcode + '\0';
	sentMessages.push(message);
}

void Messenger::AddMouseMessage(WPARAM wParam, LPARAM lParam, POINT p)
{
	std::string action = std::to_string(GetMouseAction(wParam));
	std::string message;
	if (wParam == WM_MOUSEWHEEL)
	{
		MSLLHOOKSTRUCT *mouseHook = (MSLLHOOKSTRUCT*)lParam;
		short wheelDelta = HIWORD(mouseHook->mouseData);
		message = SetMessageMouseScroll(action, wheelDelta);
	}
	else
	{
		MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
		short dx = pMouseStruct->pt.x - p.x;
		short dy = pMouseStruct->pt.y - p.y;
		message = SetMessageMouseAction(action, dx, dy);
	}
	sentMessages.push(message);
}

std::string Messenger::SetMessageMouseScroll(const std::string & action, const short & delta)
{
	return "2 " + action + ' ' + std::to_string(delta) + '\0';
}

std::string Messenger::SetMessageMouseAction(const std::string & action, const int & dx, const int & dy)
{
	return "1 " + action + ' ' + std::to_string(dx) + ' ' + std::to_string(dy) + '\0';
}

void Messenger::AddOutOfBorderMessage(const std::string & side, float ratio)
{
	sentMessages.push(side + std::to_string(ratio) + '\0');
}

int Messenger::GetKeyBoardAction(WPARAM wParam)
{
	switch (wParam)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		return 0;
	case WM_SYSKEYUP:
	case WM_KEYUP:
		return KEYEVENTF_KEYUP;
	default:
		return -1;
		break;
	}
}
int Messenger::GetMouseAction(WPARAM wParam)
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
std::mutex Messenger::mutex_;