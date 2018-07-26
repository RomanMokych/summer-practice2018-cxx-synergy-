#include "MessagesParser.h"


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

int MessagesParser::ParseMouseScrollEvent(const std::string & message)
{
	std::istringstream messageStream(message);
	std::string mouse[4] = { " " };
	
	for (size_t i = 0; i < 4; i++)
	{
		messageStream >> mouse[i];
	}

	return atoi(mouse[3].c_str());
}

float MessagesParser::ParseBorderlineEvent(const std::string & message)
{
	std::istringstream messageStream(message);
	std::string mouse[2] = { " " };
	
	for (size_t i = 0; i < 2; i++)
	{
		messageStream >> mouse[i];
	}
	
	return atof(mouse[1].c_str());
}

void MessagesParser::ParseNeighbours(const std::string & message)
{
	std::istringstream messageStream(message);
	std::string neighbours[5] = { "0" };

	for (size_t i = 0; i < 5; i++)
	{
		messageStream >> neighbours[i];
	}
	for (int i = 1; i < 5; i++)
	{
		InputHandler::Instance().neighbours[i - 1] = neighbours[i];
	}
}
