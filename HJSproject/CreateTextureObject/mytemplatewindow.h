
#pragma once
#include "mywindow.h"

//Base template Window Class
template<class DTWClass>
class MyBTWClass
{
protected:
	HWND hwnd;
	int clientWidth;
	int clientHeight;

public:
	MyBTWClass();
	virtual ~MyBTWClass() {};

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

	HWND getHWND() const;

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

template<class DTWClass>
inline MyBTWClass<DTWClass>::MyBTWClass()
{
	hwnd = nullptr;
	clientWidth = 0;
	clientHeight = 0;
}

template<class DTWClass>
LRESULT CALLBACK MyBTWClass<DTWClass>::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DTWClass* pDerivedClass = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		//생성시 넘긴 클래스에 대한 정보를 창 프로시저로 전달해 프로시저
		CREATESTRUCT* pStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		pDerivedClass = reinterpret_cast<DTWClass*>(pStruct->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pDerivedClass);

		pDerivedClass->hwnd = hwnd;
	}
	else
	{
		pDerivedClass = reinterpret_cast<DTWClass*>(
			GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pDerivedClass)
	{
		return pDerivedClass->MessageHandler(uMsg, wParam, lParam);
	}
	else { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
}

template<class DTWClass>
BOOL MyBTWClass<DTWClass>::createAndShow(	LPCWSTR lpWindowName,
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
	wcex.lpfnWndProc = DTWClass::WndProc;

	ATOM ret = RegisterClassEx(&wcex);

	hwnd = CreateWindowEx(	dwExStyle,
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

template<class DTWClass>
inline HWND MyBTWClass<DTWClass>::getHWND() const
{
	return hwnd;
}