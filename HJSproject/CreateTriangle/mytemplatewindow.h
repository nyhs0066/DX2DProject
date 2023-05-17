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

	virtual LRESULT CALLBACK MessageHandler(
		UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual PCWSTR WindowClassName() = 0;

public:
	MyBTWClass();
	virtual ~MyBTWClass() {};

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL create(LPCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int X = CW_USEDEFAULT,
		int Y = CW_USEDEFAULT,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0);
	void show(int nCmdShow);

	HWND getHWND() const;

	virtual bool init() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release() = 0;
	virtual BOOL run() = 0;
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
BOOL MyBTWClass<DTWClass>::create(	LPCWSTR lpWindowName,
									DWORD dwStyle,
									DWORD dwExStyle,
									int X,
									int Y,
									int width,
									int height,
									HWND hWndParent,
									HMENU hMenu)
{
	RECT clientArea = { X, Y, X + width, Y + height };
	AdjustWindowRectEx(&clientArea, dwStyle, 0, dwExStyle);
	clientWidth = clientArea.right - clientArea.left;
	clientHeight = clientArea.bottom - clientArea.top;

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
							0,
							0,
							clientWidth,
							clientHeight,
							hWndParent,
							hMenu,
							wcex.hInstance,
							this);

	return (hwnd ? true : false);
}

template<class DTWClass>
void MyBTWClass<DTWClass>::show(int nCmdShow)
{
	ShowWindow(hwnd, nCmdShow);
}

template<class DTWClass>
inline HWND MyBTWClass<DTWClass>::getHWND() const
{
	return hwnd;
}