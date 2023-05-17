#pragma once
#include "mygamecore.h"
#include "mysoundmanager.h"

class TestCase : public MyGameCore
{
public:
	MySound* pTest;

	bool init();
	bool frame();
	bool render();
	bool release();
};