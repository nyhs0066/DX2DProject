#pragma once
#include "myobject2d.h"
#include <random>

class MyDynamicObject2D : public MyObject2D
{
public:
	MyDynamicObject2D();
	virtual ~MyDynamicObject2D();

	virtual bool init() override;
	virtual bool frame() override;
};