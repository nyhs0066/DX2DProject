#pragma once
#include "mywindow.h"
#include "myrendermanager.h"

class TestCase : public MyWindow
{
public:
	BOOL run();

	bool init();
	bool frame();
	bool render();
	bool release();
};