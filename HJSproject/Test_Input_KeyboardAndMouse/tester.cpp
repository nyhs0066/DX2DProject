#include "tester.h"

bool TestCase::init()
{
	return true;
}

bool TestCase::frame()
{
	return true;
}

bool TestCase::render()
{
	if (MyInput::getInstance().getKeyState('A') == KEY_HOLD) 
	{
		DRAWTEXT(L"A KEY HOLD", 300, 300);
	}
	if (MyInput::getInstance().getKeyState('S') == KEY_HOLD)
	{
		DRAWTEXT(L"S KEY HOLD", 300, 330);
	}
	if (MyInput::getInstance().getKeyState('D') == KEY_HOLD)
	{
		DRAWTEXT(L"D KEY HOLD", 300, 360);
	}
	if (MyInput::getInstance().getKeyState('W') == KEY_HOLD)
	{
		DRAWTEXT(L"W KEY HOLD", 300, 390);
	}

	if (MyInput::getInstance().getKeyState(VK_F1) == KEY_HOLD)
	{
		DRAWTEXT(L"F1 KEY HOLD", 300, 420);
	}
	if (MyInput::getInstance().getKeyState(VK_INSERT) == KEY_HOLD)
	{
		DRAWTEXT(L"INSERT KEY HOLD", 300, 450);
	}
	if (MyInput::getInstance().getKeyState(VK_SHIFT) == KEY_HOLD)
	{
		DRAWTEXT(L"SHIFT KEY HOLD", 300, 480);
	}

	if(MyInput::getInstance().getKeyState(VK_LBUTTON) == KEY_HOLD)
	{
		wstring mpt;

		mpt += L"X : " + std::to_wstring(MAININPUT.getMousePt().x) + L"  ";
		mpt += L"Y : " + std::to_wstring(MAININPUT.getMousePt().y) + L"  ";

		DRAWTEXT(mpt.c_str(), 300, 510);
	}

	return true;
}

bool TestCase::release()
{
	return true;
}

GAME_RUN(My First Library Application, 600, 600)