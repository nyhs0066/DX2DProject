#pragma once
#include "myrendermanager.h"
#include "myshadermanager.h"
#include "mytextwriter.h"
#include "mytexturemanager.h"
#include "mytimer.h"
#include "myinput.h"
#include "myeffectstate.h"
#include "mysoundmanager.h"
#include "myrandom.h"
#include "myspritemanager.h"

class MyGameCore : public MyWindow
{
public:
	bool wireFrameFlag;
	int iPrevWidth;
	int iPrevHeight;

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;

	BOOL run()  override;

	MyGameCore();
	~MyGameCore();

private:
	bool coreInit();
	bool coreFrame();
	bool corePreRender();
	bool coreRender();
	bool corePostRender();
	bool coreRelease();

	bool isResized();
	bool resizeDevice();
};

