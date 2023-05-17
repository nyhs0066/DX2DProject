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





