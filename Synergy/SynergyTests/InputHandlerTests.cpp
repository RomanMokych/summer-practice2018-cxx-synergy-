#include "pch.h"
#include "gtest/gtest.h"

#include "SynergyLib/InputHandler.h"
#include "SynergyLib/Messenger.h"


TEST(InputHandler, MouseMoveEventToBorderEvent) {
	
	InputHandler::Instance().mousePosition = POINT{ 99, 0 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[1] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 100, 0 }, 100, 100);
	EXPECT_TRUE(monitorDeactivated);

	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("4 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}
TEST(InputHandler, MouseMoveEventToBorderEvent) {

	InputHandler::Instance().mousePosition = POINT{ 99, 0 };
	InputHandler::Instance().isCurrentComputerDisabled = false;
	InputHandler::Instance().neighbours[3] = "1";

	bool monitorDeactivated = InputHandler::Instance().MouseMoveEventToBorderEvent(POINT{ 100, 0 }, 100, 100);
	EXPECT_TRUE(monitorDeactivated);

	ASSERT_FALSE(Messenger::Instance().sentMessages.empty());
	EXPECT_STREQ("3 0.000000\0", Messenger::Instance().sentMessages.front().c_str());

	Messenger::Instance().sentMessages.pop();
}
