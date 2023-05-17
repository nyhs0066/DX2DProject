#pragma once
#include "myunih.h"
#include "myrendermanager.h"
#include "mywriter.h"

class MyGameCore : public MyWindow
{
public:
	MyWriter m_writer;

	BOOL run();

private:
	bool coreInit();
	bool coreFrame();
	bool coreRender();
	bool coreRelease();
};