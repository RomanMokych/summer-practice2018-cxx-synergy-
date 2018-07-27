#include "MessagesParser.h"

void MessagesParser::ParseMouseEvent(const std::string& message, int* x, int* y, int* action)
{
	SplitMessages(4, message);
	*action = atoi(messages[1].c_str());
	*x = atoi(messages[2].c_str());
	*y = atoi(messages[3].c_str());
	messages.clear();
}

void MessagesParser::ParseKeyboardActionEvent(const std::string & message, int * key, int * state)
{
	SplitMessages(3,message);
	*state = atoi(messages[1].c_str());
	*key = (unsigned short)atoi(messages[2].c_str());
	messages.clear();
}

int MessagesParser::ParseMouseScrollEvent(const std::string & message)
{
	SplitMessages(3, message);
	int delta = atoi(messages[2].c_str());
	messages.clear();
	return delta;
}

float MessagesParser::ParseBorderlineEvent(const std::string & message)
{
	SplitMessages(2, message);
	float ratio = atof(messages[1].c_str());
	messages.clear();
	return ratio;
}

void MessagesParser::ParseNeighbours(const std::string & message)
{
	SplitMessages(5, message);
	for (int i = 1; i < 5; i++)
	{
		InputHandler::Instance().neighbours[i - 1] = messages[i];
	}
}

void MessagesParser::SplitMessages(const int & size, const std::string & message)
{
	std::istringstream messageStream(message);
	messages.resize(size);
	for (int i = 0; i < size; i++)
	{
		messageStream >> messages[i];
	}
}

std::vector <std::string> MessagesParser::messages;