#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mydynamicobject.h"
#include "mycollision.h"
#include "mybackgroundobject.h"
#include "mycamera.h"

class TestCase : public MyGameCore
{
public:
	MyCamera mainCam;
	MyCamera subCam;
	MyRect BoundaryRect;
	MyBackGroundObject BGObj;
	MyMovementTestDummy dummy;
	MyObject2D sup;

	vector<MyMapObject2D*> tileObjects;

	bool init();
	bool frame();
	bool render();
	bool release();
};