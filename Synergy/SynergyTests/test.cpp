#include "pch.h"
#include "SynergyLib/MessagesParser.h"

TEST(MessagesParser, ParseMouseMoveEvent) {
  
	int x = 0;
	int y = 0;
	int w = 0;

	MessagesParser::ParseMouseEvent("1 0 0 1 2", &x, &y, &w);

	EXPECT_EQ(1, x);
	EXPECT_EQ(2, y);
	EXPECT_EQ(0, w);
}

TEST(MessagesParser, ParseMouseActionEventLeftClick) {

	int x = 0;
	int y = 0;
	int w = 0;

	MessagesParser::ParseMouseEvent("1 2 0 1 2", &x, &y, &w);

	EXPECT_EQ(1, x);
	EXPECT_EQ(2, y);
	EXPECT_EQ(2, w);
}

TEST(MessagesParser, ParseMouseActionEventRightClick) {

	int x = 0;
	int y = 0;
	int w = 0;

	MessagesParser::ParseMouseEvent("1 8 0 1 2", &x, &y, &w);

	EXPECT_EQ(1, x);
	EXPECT_EQ(2, y);
	EXPECT_EQ(8, w);
}

TEST(MessagesParser, CtrlPressDown) {
	int key = 0;
	int state = 0;

	MessagesParser::ParseKeyboardActionEvent("0 0 2 162",&key,&state);

	EXPECT_EQ(162, key);
	EXPECT_EQ(0, state);

}

TEST(MessagesParser, CtrlPressUp) {
	int key = 0;
	int state = 0;

	MessagesParser::ParseKeyboardActionEvent("0 2 2 162", &key, &state);

	EXPECT_EQ(162, key);
	EXPECT_EQ(2, state);

}