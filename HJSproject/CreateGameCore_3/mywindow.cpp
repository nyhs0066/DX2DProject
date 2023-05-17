#include "mywindow.h"

HWND MyWindow::hwnd = NULL;
int MyWindow::cWidth = 0;
int MyWindow::cHeight = 0;

LRESULT CALLBACK MyWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MyWindow* derivedClass = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* crt = reinterpret_cast<CREATESTRUCT*>(lParam);
		derivedClass = reinterpret_cast<MyWindow*>(crt->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)derivedClass);

		derivedClass->hwnd = hwnd;
	}
	else
	{
		derivedClass = (MyWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (derivedClass) { return derivedClass->msgHandler(uMsg, wParam, lParam); }
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL MyWindow::createAndShow(LPCWSTR lpWindowName,
	DWORD dwStyle,
	int width,
	int height,
	DWORD dwExStyle,
	int X,
	int Y,
	HWND hWndParent,
	HMENU hMenu)
{
	RECT clientArea = { X, Y, X + width, Y + height };
	AdjustWindowRectEx(&clientArea, dwStyle, 0, dwExStyle);
	cWidth = width;
	cHeight = height;
	width = clientArea.right - clientArea.left;
	height = clientArea.bottom - clientArea.top;

	int centerX = (GetSystemMetrics(SM_CXFULLSCREEN) - width) / 2;
	int centerY = (GetSystemMetrics(SM_CYFULLSCREEN) - height) / 2;

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = WindowClassName();
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.lpfnWndProc = WndProc;

	ATOM ret = RegisterClassEx(&wcex);

	hwnd = CreateWindowEx(dwExStyle,
		wcex.lpszClassName,
		lpWindowName,
		dwStyle,
		centerX,
		centerY,
		width,
		height,
		hWndParent,
		hMenu,
		wcex.hInstance,
		this);

	if (!hwnd) { return FALSE; }

	ShowWindow(hwnd, SW_SHOWDEFAULT);

	return TRUE;
}

BOOL MyWindow::run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (msg.message == WM_QUIT) { return false; }
		else
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else { break; }
		}
	}

	return true;
}

PCWSTR MyWindow::WindowClassName()
{
	return L"CreateGameCore_3";
}

LRESULT MyWindow::msgHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, L"Quit Application?", L"Close Box", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}

		return 0;
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool MyWindow::init()
{
	return true;
}

bool MyWindow::frame()
{
	return true;
}

bool MyWindow::render()
{
	return true;
}

bool MyWindow::release()
{
	return true;
}