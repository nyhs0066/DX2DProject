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
	MyPlayer playerObj;
	FLOAT timer;
	UINT counter;
	vector<wstring> spriteName;

	bool init();
	bool frame();
	bool render();
	bool release();
};