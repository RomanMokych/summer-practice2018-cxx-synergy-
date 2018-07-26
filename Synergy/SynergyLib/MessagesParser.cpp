#include "MessagesParser.h"

#include <sstream>

MessagesParser::MessagesParser()
{
}


MessagesParser::~MessagesParser()
{
}

void MessagesParser::ParseMouseEvent(const std::string& message, int* x, int* y, int* action)
{
	std::istringstream messageStream(message);
	std::string mouse[5] = { " " };

	for (size_t i = 0; i < 5; i++)
	{
		messageStream >> mouse[i];
	}

	*action = atoi(mouse[1].c_str());
	*x = atoi(mouse[3].c_str());
	*y = atoi(mouse[4].c_str());
}

void MessagesParser::ParseKeyboardActionEvent(const std::string & message, int * key, int * state)
{
	std::istringstream messageStream(message);
	std::string code[4] = { " " };

	for (int i = 0; i < 4; i++)
	{
		messageStream >> code[i];
	}
	
	*state = atoi(code[1].c_str());
	*key = (unsigned short)atoi(code[3].c_str());
}

void MessagesParser::ParseMouseScrollEvent(const std::string & message, int * delta)
{
	std::istringstream messageStream(message);
	std::string mouse[4] = { " " };
	
	for (size_t i = 0; i < 4; i++)
	{
		messageStream >> mouse[i];
	}

	*delta = atoi(mouse[3].c_str());
}
