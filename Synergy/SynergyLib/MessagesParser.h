#pragma once

#include <string>

class MessagesParser
{
public:
	MessagesParser();
	~MessagesParser();

	static void ParseMouseEvent(const std::string& message, int* x, int* y, int* w);
};

