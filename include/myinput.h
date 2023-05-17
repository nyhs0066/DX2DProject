#pragma once
#include "myunih.h"
#include "mywindow.h"

#define MY_MAXINPUT 256

enum MYKEYSTATE { KEY_FREE, KEY_DOWN, KEY_HOLD, KEY_UP };

class MyInput : public Singleton<MyInput>
{
	friend class Singleton<MyInput>;

private:
	POINT m_mousePt;
	DWORD m_dwKeyState[MY_MAXINPUT];

	DWORD keyTemp;

	MyInput();
	~MyInput();

public:
	POINT getMousePt();
	UINT getKeyState(SHORT vKey);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define MAININPUT MyInput::getInstance()