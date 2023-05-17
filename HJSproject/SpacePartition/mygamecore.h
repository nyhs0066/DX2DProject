#pragma once
#include "myspacepartition.h"
#include "myplayer.h"
#include <windows.h>
#include <time.h>

class MyGameCore
{
public:
	MySpacePartition* pSpace;
	MyObject* pPlayer;
	map<int, MyObject*> allObjlist;
	vector<MyObject*> dynamicObjList;
	vector<MyObject*> collisionList;

public:
	MyGameCore();
	~MyGameCore();

	void initialization();
	void frame(float deltaT, float gameT);
	void draw();
	void release();
	void run();
};
