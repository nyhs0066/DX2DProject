#pragma once
#include "myunih.h"

class MyWindow
{
public:
	static HWND hwnd;
	static int cWidth;
	static int cHeight;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	MyWindow() {};
	virtual ~MyWindow() {};

	BOOL createAndShow(LPCWSTR lpWindowName,
		DWORD dwStyle,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT,
		DWORD dwExStyle = 0,
		int X = 0,
		int Y = 0,
		HWND hWndParent = 0,
		HMENU hMenu = 0);

	virtual BOOL run();

	virtual PCWSTR WindowClassName();
	virtual LRESULT CALLBACK msgHandler(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};

#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lCmdLine, int nCmdShow) {
#define GAME_WNDCNSHOW(s, x, y) TestCase instance; bool createFlag = instance.createAndShow(L#s, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, x, y); if(!createFlag) { return false; } instance.run(); return 0;
#define GAME_END }
#define GAME_RUN(s, x, y) GAME_START GAME_WNDCNSHOW(s, x, y) GAME_END

