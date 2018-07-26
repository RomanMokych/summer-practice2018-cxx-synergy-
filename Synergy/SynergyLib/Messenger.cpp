#include "Messenger.h"



Messenger & Messenger::Instance()
{
	// TODO: insert return statement here
	std::unique_lock <std::mutex> unique(mutex_);
	static Messenger instance;
	return instance;
}

void Messenger::AddKeyboardMessage(WPARAM wParam, LPARAM lParam, int vkCode)
{
	std::string action = std::to_string(GetKeyBoardAction(wParam));
	std::string lparam = std::to_string(lParam);
	std::string kcode = std::to_string(vkCode);
	std::string message = "0 " + action + ' ' + lparam + ' ' + kcode + '\0';
	sentMessages.push(message);
}

void Messenger::AddMouseMessage(WPARAM wParam, LPARAM lParam, POINT p)
{
	std::string action = std::to_string(GetMouseAction(wParam));
	std::string delta;
	std::string message;
	std::string lparam = std::to_string(lParam);
	if (wParam == WM_MOUSEWHEEL)
	{
		MSLLHOOKSTRUCT *mouseHook = (MSLLHOOKSTRUCT*)lParam;
		short wheelDelta = HIWORD(mouseHook->mouseData);
		delta = std::to_string(wheelDelta);
		message = "2 " + action + ' ' + lparam + ' ' + delta + '\0';
	}
	else
	{
		MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
		short dx = pMouseStruct->pt.x - p.x;
		short dy = pMouseStruct->pt.y - p.y;
		delta = std::to_string(dx) + ' ' + std::to_string(dy);
		message = "1 " + action + ' ' + lparam + ' ' + delta + '\0';
	}
	sentMessages.push(message);
}

void Messenger::AddOutOfBorderMessage(const std::string & side, float ratio)
{
	sentMessages.push(side + std::to_string(ratio) + '\0');
}

Messenger::Messenger()
{
}


Messenger::~Messenger()
{
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
