#pragma once
#include "myunih.h"
#include "myrendermanager.h"
#include "myshadermanager.h"
#include "mytexturemanager.h"
#include "mywriter.h"
#include "myinput.h"
#include "mytimer.h"
#include "mybaseobject.h"
#include "mystate.h"

class MyGameCore : public MyWindow
{
public:
	MyRectObject mapOBJ;

	BOOL run();

private:
	bool coreInit();
	bool coreFrame();
	bool coreRender();
	bool coreRelease();

	bool render();
};