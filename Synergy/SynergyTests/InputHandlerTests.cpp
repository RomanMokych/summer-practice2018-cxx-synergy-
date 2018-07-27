#include "pch.h"
#include "gtest/gtest.h"
#include "SynergyLib/InputHandler.h"
#include "SynergyLib/Messenger.h"


TEST(InputHandler, MouseMoveOutOfBorderEventToRight) {
	
	InputHandler::Instance().mousePosition = POINT{ 99, 0 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[1] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 100, 0 }, 100, 100);
	
	EXPECT_TRUE(monitorDeactivated);
	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("4 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}
TEST(InputHandler, MouseMoveOutOfBorderEventToLeft) {

	InputHandler::Instance().mousePosition = POINT{ 0, 0 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[3] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ -1, 0 }, 100, 100);
	
	EXPECT_TRUE(monitorDeactivated);
	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("3 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}
TEST(InputHandler, MouseMoveOutOfBorderEventToTop) {

	InputHandler::Instance().mousePosition = POINT{ 0, 0 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[0] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 0, -1 }, 100, 100);
	
	EXPECT_TRUE(monitorDeactivated);
	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("5 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}

TEST(InputHandler, MouseMoveOutOfBorderEventToBottom) {

	InputHandler::Instance().mousePosition = POINT{ 0, 99 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[2] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 0, 100 }, 100, 100);
	
	EXPECT_TRUE(monitorDeactivated);
	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("6 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}

TEST(InputHandler, MouseMoveOutOfBorderEventError) {

	InputHandler::Instance().mousePosition = POINT{ 0, 99 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[2] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 0, 100 }, 100, 100);
	
	EXPECT_TRUE(monitorDeactivated);
	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("6 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}

TEST(InputHandler, MouseMoveEventToBorderEventError) {

	InputHandler::Instance().mousePosition = POINT{ 0, 99 };
	InputHandler::Instance().isCurrentComputerDisabled = true;
	InputHandler::Instance().neighbours[2] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 0, 100 }, 100, 100);
	
	EXPECT_FALSE(monitorDeactivated);
	ASSERT_TRUE(Messenger::Instance().sentMessages.empty());

}
TEST(InputHandler, MouseMoveEventToBorderEventCondition) {

	InputHandler::Instance().mousePosition = POINT{ 100, 99 };
	InputHandler::Instance().neighbours[3] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 100, 0}, 100, 100);
	
	EXPECT_FALSE(monitorDeactivated);
	ASSERT_TRUE(Messenger::Instance().sentMessages.empty());

}