#pragma once
#include "mygamecore.h"
#include "mysound.h"

class TestCase : public MyGameCore
{
public:
	MySounder test;

	bool init();
	bool frame();
	bool render();
	bool release();
};