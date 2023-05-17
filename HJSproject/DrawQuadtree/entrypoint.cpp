//#include "mywclass.h"
#include "mygamecore.h"

#define GAME_START	int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
#define GAME_WINDOW(s, x, y) MyDTWindow test; BOOL createFlag = test.create(s, WS_OVERLAPPEDWINDOW, 0, 0, 0, x, y);  if (!createFlag) { return 0; } test.show(nCmdShow); test.run(); return 0;
#define GAME_END	}
#define GAME_RUN(s, x, y) GAME_START GAME_WINDOW(s, x, y) GAME_END

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	PWSTR lpCmdLine, int nCmdShow)
{
	MyDxWindow test;
	
	//create window and show window
	BOOL createFlag = test.createAndShow(L"My Second Window", WS_OVERLAPPEDWINDOW, 600, 600);
	if (!createFlag) { return 0; }

	//loop
	test.run();

	return 0;
}
