#include "MyInput.h"

MyInput::MyInput()
{

}

MyInput::~MyInput()
{
	release();
}

SHORT MyInput::getKState(DWORD key)
{
	if (0 <= key && key < 256) { return dwKeyState[key]; }
	return -1;
}

POINT MyInput::getMoustPt()
{
	return mousePt;
}

bool MyInput::init()
{
	ZeroMemory(dwKeyState, sizeof(dwKeyState));
	mousePt.x = 0;
	mousePt.y = 0;

	return true;
}

bool MyInput::frame()
{
	GetCursorPos(&mousePt);
	ScreenToClient(MyWindow::hwnd, &mousePt);

	SHORT state;
	for (int i = 0; i < 256; i++) 
	{ 
		state = GetAsyncKeyState(i);
		
		if (state & 0x8000)
		{
			if (dwKeyState[i] == KS_FREE || dwKeyState[i] == KS_UP) 
			{ 
				dwKeyState[i] = KS_DOWN;
			}
			else { dwKeyState[i] = KS_HOLD; }
		}
		else
		{
			if (dwKeyState[i] == KS_DOWN || dwKeyState[i] == KS_HOLD)
			{
				dwKeyState[i] = KS_UP;
			}
			else { dwKeyState[i] = KS_FREE; }
		}
	}
	return true;
}

bool MyInput::render()
{
	return true;
}

bool MyInput::release()
{
	return true;
}
