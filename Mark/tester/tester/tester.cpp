#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <thread>
//#include <chrono>
using namespace std;

void KeyboardClicks() {
		for (char i = 0; i < 255; i++)
		{
			int keyState = GetAsyncKeyState(i);
			if (keyState == 1 || keyState == -32767)
			{
				std::cout << i << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(0));
		}	
}


int MouseClick(int key)
{
	return (GetAsyncKeyState(key) & 0x100 != 0);
}

POINT MouseMove() {
	POINT mouse;
	GetCursorPos(&mouse);
	//cout << "x :" << mouse.x << endl;  Отображения по оси Х (относительно экрана)
	//cout << "y :" << mouse.y << endl;  Отображения по оси У (относительно экрана)
	return mouse;
}
int main()
{
	while(1){
		KeyboardClicks();
	}
}