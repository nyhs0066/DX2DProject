#include "mytwindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lCmdLine, int nCmdShow)
{
	MyWindow test;

	bool createFlag = test.createAndShow(L"Create Texture Object1", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return false; }

	test.run();

	return 0;
}