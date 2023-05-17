#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mydynamicobject.h"
#include "mycollision.h"
#include "mybackgroundobject.h"

class TestCase : public MyGameCore
{
public:
	MyRect BoundaryRect;
	MyMovementTestDummy dummy;
	MyObject2D sup;

	vector<MyMapObject2D*> tileObjects;

	bool init();
	bool frame();
	bool render();
	bool release();
};