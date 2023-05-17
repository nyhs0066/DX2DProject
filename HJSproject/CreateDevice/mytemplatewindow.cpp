#include "mytemplatewindow.h"

LRESULT MyDTWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HBRUSH hBrush = (HBRUSH)(COLOR_WINDOW + 1);
		RECT rect = {0, 0, 300, 300};
		HDC hdc;

		hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &rect, hBrush);
		TextOut(hdc, 100, 100, L"My First String", 15);

		EndPaint(hwnd, &ps);
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

const wchar_t* MyDTWindow::WindowClassName()
{
	return L"Derived Window";
}

bool MyDTWindow::init()
{
	return false;
}

bool MyDTWindow::frame()
{
	return false;
}

bool MyDTWindow::render()
{
	return false;
}

bool MyDTWindow::release()
{
	return false;
}

BOOL MyDTWindow::run()
{
	init();

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			frame();
			render();
		}
	}

	release();
	return TRUE;
}
