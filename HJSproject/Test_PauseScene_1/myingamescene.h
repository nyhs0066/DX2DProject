#pragma once
#include "myscenemanager.h"

class MyInGameScene : public MyScene
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

	std::vector<MyEffect*> ePresetList;

	std::list<MyEffect*> effectList;

	std::list<MyEffect*>::iterator it;
	std::list<MyEffect*>::const_iterator cit;

	std::vector<std::list<MyEffect*>::const_iterator> deleteList;

	MyObject2D* pHitDummy;

	MyUserInterface* pEmptyBar;
	MyUserInterface* pBar;
	MyUserInterface  testBar;

	MyUIDialog testUI;

	FLOAT timer;
	FLOAT hitTimer;

	bool loadResource();
	
	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};