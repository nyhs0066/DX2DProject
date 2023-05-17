#pragma once
#include "myspacepartition.h"
#include "myplayer.h"

class MyGameCore : public MyDxDevicePreset
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
