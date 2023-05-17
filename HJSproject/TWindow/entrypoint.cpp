#include "twindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MyWindow test;

	bool createFlag = test.createAndShow(L"My TWindow", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return false; }

	test.run();
	return 0;
}
