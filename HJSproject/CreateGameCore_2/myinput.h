#pragma once
#include "mywindow.h"

enum KEY_STATE { KS_FREE, KS_DOWN, KS_UP, KS_HOLD };

class MyInput : public Singleton<MyInput>
{
	friend class Singleton<MyInput>;
private:
	POINT mousePt;
	DWORD dwKeyState[0x0100];

	MyInput();
	~MyInput();

public:
	SHORT getKState(DWORD key);
	POINT getMoustPt();

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define I_INPUT MyInput::getInstance()