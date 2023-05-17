#include "myinput.h"

MyInput::MyInput()
{
	m_mousePt = { 0 };
	ZeroMemory(&m_dwKeyState, sizeof(m_dwKeyState));
}

MyInput::~MyInput()
{
	release();
}

POINT MyInput::getMousePt()
{
	return m_mousePt;
}

UINT MyInput::getKeyState(SHORT vKey)
{
	if (0 < vKey && vKey < 256) { return m_dwKeyState[vKey]; }
	else { return -1; }
}

bool MyInput::init()
{
	return true;
}

bool MyInput::frame()
{
	//커서 좌표를 화면 좌표로 받고
	GetCursorPos(&m_mousePt);

	//클라이언트 좌표계로 화면 좌표를 변환한다.
	ScreenToClient(MyWindow::hwnd, &m_mousePt);

	keyTemp = 0;

	for (int i = 0; i < MY_MAXINPUT; i++)
	{
		keyTemp = GetAsyncKeyState(i);

		if (keyTemp & 0x8000)
		{
			if (m_dwKeyState[i] == KEY_FREE || 
				m_dwKeyState[i] == KEY_UP) { m_dwKeyState[i] = KEY_DOWN; }
			else { m_dwKeyState[i] = KEY_HOLD; }
		}
		else
		{
			if (m_dwKeyState[i] == KEY_HOLD ||
				m_dwKeyState[i] == KEY_DOWN) { m_dwKeyState[i] = KEY_UP; }
			else { m_dwKeyState[i] = KEY_FREE; }
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