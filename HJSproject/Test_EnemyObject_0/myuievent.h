#pragma once
#include "myuserinterface.h"
#include "myscenemanager.h"

class MyUIEvent
{
public:
	MyUIEvent();
	~MyUIEvent();

	virtual void operator()() = 0;
};

class UIButton_Play : public MyUIEvent
{
public:
	void operator()() override;
};