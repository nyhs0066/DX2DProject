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

	MyEffectPreset preset1;
	std::list<MyEffect*> effectList;

	std::list<MyEffect*>::iterator it;
	std::list<MyEffect*>::const_iterator cit;

	bool init();
	bool frame();
	bool render();
	bool release();
};