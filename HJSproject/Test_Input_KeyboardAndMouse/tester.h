#pragma once
#include "mygamecore.h"

class TestCase : public MyGameCore
{
public:
	bool init();
	bool frame();
	bool render();
	bool release();
};