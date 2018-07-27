#pragma once
#include <sstream>
#include <string>
#include <vector>
#include "InputHandler.h"

class MessagesParser
{
public:

	static void ParseMouseEvent(const std::string& message, int* x, int* y, int* action);
	static void ParseKeyboardActionEvent(const std::string& message, int * key , int *state);
	static int ParseMouseScrollEvent(const std::string& message);
	static float ParseBorderlineEvent(const std::string& message);
	static void ParseNeighbours(const std::string& message);
private:
	static std::vector <std::string> messages;
	static void SplitMessages(const int& size,const std::string& message);
};

