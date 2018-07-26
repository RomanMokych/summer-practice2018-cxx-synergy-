#pragma once
#include <mutex>
#include <queue>
#include <string.h>
#include <string>
#include <cstdlib>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <windows.h>

class Messenger
{
public:
	std::queue<std::string> sentMessages;
	static Messenger & Instance();
	void AddKeyboardMessage(WPARAM wParam, LPARAM lParam, int vkCode);
	void AddMouseMessage(WPARAM wParam, LPARAM lParam, POINT p);
	void AddOutOfBorderMessage(const std::string & side, float ratio);
	char recievedMessage[1024];
private:
	Messenger();
	~Messenger();
	static std::mutex mutex_;
	int GetKeyBoardAction(WPARAM wParam);
	int GetMouseAction(WPARAM wParam);
	Messenger(Messenger const&) = delete;
	Messenger(Messenger const&&) = delete;
	Messenger operator=(Messenger const&) = delete;
	Messenger operator=(Messenger const&&) = delete;
};

