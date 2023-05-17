#pragma once
#include "myunih.h"
#include "myrendermanager.h"

//Base template Window Class
template<class Derived>
class MyBTWindow
{
protected:
	HWND hwnd;
	int clientWidth;
	int clientHeight;

public:
	MyBTWindow();
	virtual ~MyBTWindow() {};

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL createAndShow(LPCWSTR lpWindowName,
		DWORD dwStyle,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT,
		DWORD dwExStyle = 0,
		int X = 0,
		int Y = 0,
		HWND hWndParent = 0,
		HMENU hMenu = 0);

	HWND	getHWND();
	int		getCWidth();
	int		getCHeight();

	virtual BOOL run() = 0;

	virtual LRESULT CALLBACK MessageHandler(
		UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual PCWSTR WindowClassName() = 0;

protected:
	virtual bool init() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;
};

template<class Derived>
inline MyBTWindow<Derived>::MyBTWindow()
{
	hwnd = NULL;
	clientWidth = 0;
	clientHeight = 0;
}

template<class Derived>
LRESULT CALLBACK MyBTWindow<Derived>::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Derived* pDerivedClass = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		pDerivedClass = reinterpret_cast<Derived*>(pStruct->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pDerivedClass);

		pDerivedClass->hwnd = hwnd;
	}
	else
	{
		pDerivedClass = reinterpret_cast<Derived*>(
			GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pDerivedClass)
	{
		return pDerivedClass->MessageHandler(uMsg, wParam, lParam);
	}
	else { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
}

template<class Derived>
BOOL MyBTWindow<Derived>::createAndShow(LPCWSTR lpWindowName,
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
	clientWidth = width;
	clientHeight = height;
	width = clientArea.right - clientArea.left;
	height = clientArea.bottom - clientArea.top;

	int centerX = (GetSystemMetrics(SM_CXFULLSCREEN) - clientWidth) / 2;
	int centerY = (GetSystemMetrics(SM_CYFULLSCREEN) - clientHeight) / 2;

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = WindowClassName();
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.lpfnWndProc = Derived::WndProc;

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

template<class Derived>
inline HWND MyBTWindow<Derived>::getHWND() { return hwnd; }

template<class Derived>
inline int MyBTWindow<Derived>::getCWidth() { return clientWidth; }

template<class Derived>
inline int MyBTWindow<Derived>::getCHeight() { return clientHeight; }

class MyWindow : public MyBTWindow<MyWindow>
{
public:
	virtual BOOL run() override;

	virtual LRESULT CALLBACK MessageHandler(
		UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual PCWSTR WindowClassName() override;

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};