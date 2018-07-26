#pragma once
#include <sstream>
#include <string>
#include "InputHandler.h"

class MessagesParser
{
public:
	MessagesParser();
	~MessagesParser();

	static void ParseMouseEvent(const std::string& message, int* x, int* y, int* action);
	static void ParseKeyboardActionEvent(const std::string& message, int * key , int *state);
	static int ParseMouseScrollEvent(const std::string& message);
	static float ParseBorderlineEvent(const std::string& message);
	static void ParseNeighbours(const std::string& message);
};

