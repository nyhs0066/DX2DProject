#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mycollision.h"
#include "mybackgroundobject.h"
#include "mycamera.h"
#include "myspritemanager.h"
#include "myeffect.h"

class TestCase : public MyGameCore
{
public:
	MyCamera mainCam;
	MyRect BoundaryRect;

	MyPlayer2D test;

	MyBackGroundObject BGObj;
	//MyMovementTestDummy dummy;

	bool init();
	bool frame();
	bool render();
	bool release();
};