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
#include "myspacepartition.h"
#include "myball.h"

class TestCase : public MyGameCore
{
public:
	QuadTree space;

	MyCamera mainCam;
	MyRect BoundaryRect;

	MyBackGroundObject BGObj;
	MyMovementTestDummy dummy;

	std::list<MyBall*> ballList;
	vector<MyObject2D*> csList;

	bool init();
	bool frame();
	bool render();
	bool release();
};