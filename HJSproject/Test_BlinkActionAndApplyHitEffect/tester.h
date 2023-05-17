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
#include "myuserinterface.h"

#define FIXFRAMET 1.0f / 60.0f

class TestCase : public MyGameCore
{
public:
	vector<wstring> rPaths;

	QuadTree space;

	MyCamera mainCam;
	MyRect BoundaryRect;

	MyBackGroundObject BGObj;
	MyMovementTestDummy dummy;

	MyMapObject* platForms;
	vector<MyObject2D*> cList;
	MyRect instRt;

	MyEffectPreset preset1;
	MyEffectPreset preset2;

	std::list<MyEffect*> effectList;

	std::list<MyEffect*>::iterator it;
	std::list<MyEffect*>::const_iterator cit;

	MyObject2D* pHitDummy;

	FLOAT timer;
	FLOAT hitTimer;

public:
	bool loadResource();

	bool init();
	bool frame();
	bool render();
	bool release();
};