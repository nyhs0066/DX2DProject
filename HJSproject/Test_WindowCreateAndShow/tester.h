#pragma once
#include "mywindow.h"

class TestCase : public MyWindow
{
public:
	bool init();
	bool frame();
	bool render();
	bool release();
};