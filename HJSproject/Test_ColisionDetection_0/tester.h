#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mydynamicobject.h"
#include "mycollision.h"

class TestCase : public MyGameCore
{
public:
	MyMapObject mapObj;
	MyPlayer playerObj;

	vector<MyDynamicObject*> DynamicObjectList;

	bool init();
	bool frame();
	bool render();
	bool release();
};