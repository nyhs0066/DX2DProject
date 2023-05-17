#pragma once
#include "mywindow.h"

enum KEY_STATE { KS_FREE, KS_DOWN, KS_UP, KS_HOLD };

class MyInput
{
public:
	POINT mousePt;
	DWORD dwKeyState[0x0100];

	SHORT getKState(DWORD key);

	bool init();
	bool frame();
	bool render();
	bool release();
};

