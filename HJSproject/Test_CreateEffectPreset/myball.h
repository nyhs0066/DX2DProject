#pragma once
#include "myobject2d.h"

class MyBall : public MyObject2D
{
public:
	bool init() override;
	bool frame() override;

	bool create(MyRect bRect);
};