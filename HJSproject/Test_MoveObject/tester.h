#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"

class TestCase : public MyGameCore
{
public:
	MyMapObject2F mapObj;
	MyPlayer2F playerObj;

	bool init();
	bool frame();
	bool render();
	bool release();
};