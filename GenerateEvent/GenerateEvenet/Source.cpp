#include "Emulator.h"

int main()
{
	while (true)
	{
		Emulator::MouseMove(rand() % 10, rand() % 10);
		Sleep(30);
	}
	system("pause");
	return 0;
}