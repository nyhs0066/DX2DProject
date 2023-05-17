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

	MyBackGroundObject BGObj;
	MyMovementTestDummy dummy;
	MyObject2D sup;

	vector<MyObject2D*> m_supList;

	int tx,ty;

	//std::list<MyEffect*> effectList;

	bool init();
	bool frame();
	bool render();
	bool release();
};