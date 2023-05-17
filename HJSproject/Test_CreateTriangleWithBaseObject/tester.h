#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"

class TestCase : public MyGameCore
{
public:
	MyBaseObject test;

	bool init();
	bool frame();
	bool render();
	bool release();
};