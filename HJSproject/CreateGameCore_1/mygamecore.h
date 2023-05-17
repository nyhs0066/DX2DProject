#pragma once
#include "myunih.h"
#include "myrendermanager.h"
#include "mywriter.h"
#include "myinput.h"
#include "mytimer.h"

class MyGameCore : public MyWindow
{
public:
	MyWriter m_writer;
	MyInput m_input;
	MyHighResolutionTimer m_timer;

	BOOL run();

private:
	bool coreInit();
	bool coreFrame();
	bool coreRender();
	bool coreRelease();

	bool render();
};