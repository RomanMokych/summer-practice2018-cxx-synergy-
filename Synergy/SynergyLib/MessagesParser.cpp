#include "MessagesParser.h"

#include <sstream>

MessagesParser::MessagesParser()
{
}


MessagesParser::~MessagesParser()
{
}

void MessagesParser::ParseMouseEvent(const std::string& message, int* x, int* y, int* w)
{
	std::istringstream messageStream(message);

	std::string mouse[5] = { " " };
	for (size_t i = 0; i < 5; i++)
	{
		messageStream >> mouse[i];
	}

	*w = atoi(mouse[1].c_str());
	
	*x = atoi(mouse[3].c_str());
	*y = atoi(mouse[4].c_str());
}
