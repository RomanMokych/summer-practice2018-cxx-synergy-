#include "pch.h"
#include "SynergyLib/Messenger.h"
#include "SynergyLib/MessagesParser.h"

TEST(Messenger, ConvertingKeyboardActions) {
	EXPECT_EQ(2, Messenger::Instance().GetKeyBoardAction(257));
}


TEST(Messenger, ConvertingMouseActions) {
	EXPECT_EQ(MOUSEEVENTF_MOVE, Messenger::Instance().GetMouseAction(WM_MOUSEMOVE));
}


TEST(Messenger, CtrlPressed) {
	Messenger::Instance().AddKeyboardMessage(260, 162);
	std::string temp = Messenger::Instance().sentMessages.front();
	std::string s2 = "0 0 162";
	EXPECT_STREQ(s2.c_str(),temp.c_str());
	Messenger::Instance().sentMessages.pop();
}

TEST(Messenger, CtrlRelease) {
	Messenger::Instance().AddKeyboardMessage(257, 162);
	std::string temp = Messenger::Instance().sentMessages.front();
	std::string s2 = "0 2 162";
	EXPECT_STREQ(s2.c_str(), temp.c_str());
	Messenger::Instance().sentMessages.pop();
}

TEST(Messenger, KeyBoardSwitchCheck) {
	
	EXPECT_EQ(0, Messenger::Instance().GetKeyBoardAction(WM_KEYDOWN));
	EXPECT_EQ(0, Messenger::Instance().GetKeyBoardAction(WM_SYSKEYDOWN));

	EXPECT_EQ(KEYEVENTF_KEYUP, Messenger::Instance().GetKeyBoardAction(WM_KEYUP));
	EXPECT_EQ(KEYEVENTF_KEYUP, Messenger::Instance().GetKeyBoardAction(WM_SYSKEYUP));

	EXPECT_EQ(-1, Messenger::Instance().GetKeyBoardAction(0x111));

}

TEST(Messenger, MouseSwitchCheck) {

	EXPECT_EQ(MOUSEEVENTF_LEFTDOWN, Messenger::Instance().GetMouseAction(WM_LBUTTONDOWN));
	EXPECT_EQ(MOUSEEVENTF_LEFTUP, Messenger::Instance().GetMouseAction(WM_LBUTTONUP));
	
	EXPECT_EQ(MOUSEEVENTF_MIDDLEDOWN, Messenger::Instance().GetMouseAction(WM_MBUTTONDOWN));
	EXPECT_EQ(MOUSEEVENTF_MIDDLEUP, Messenger::Instance().GetMouseAction(WM_MBUTTONUP));

	EXPECT_EQ(MOUSEEVENTF_RIGHTDOWN, Messenger::Instance().GetMouseAction(WM_RBUTTONDOWN));
	EXPECT_EQ(MOUSEEVENTF_RIGHTUP, Messenger::Instance().GetMouseAction(WM_RBUTTONUP));
	
	EXPECT_EQ(MOUSEEVENTF_XDOWN, Messenger::Instance().GetMouseAction(WM_XBUTTONDOWN));
	EXPECT_EQ(MOUSEEVENTF_XUP, Messenger::Instance().GetMouseAction(WM_XBUTTONUP));
	
	EXPECT_EQ(MOUSEEVENTF_WHEEL, Messenger::Instance().GetMouseAction(WM_MOUSEWHEEL));
	EXPECT_EQ(MOUSEEVENTF_MOVE, Messenger::Instance().GetMouseAction(WM_MOUSEMOVE));
	
	EXPECT_EQ(-1, Messenger::Instance().GetMouseAction(0X111));
}