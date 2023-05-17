#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mydynamicobject.h"

class TestCase : public MyGameCore
{
public:
	MyMapObject2F mapObj;

	bool init();
	bool frame();
	bool render();
	bool release();
};