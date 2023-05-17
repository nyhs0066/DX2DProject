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
#include "myuserinterface.h"

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

	ID3D11BlendState* temp;
	vector<ID3D11BlendState*> bStateArr;
	int c[100];
	int cnt;

	MyUserInterface* pTestUIButton;

public:
	bool init();
	bool frame();
	bool render();
	bool release();

	HRESULT createBlendState();
	HRESULT createAlphaBlendState();

	//»¡°­ - ÃÊ·Ï - ÆÄ¶û - ³ë¶û - Ã»·Ï - ÀÚÁÖ
	HRESULT createRBState();
	HRESULT createGBState();
	HRESULT createBBState();
	HRESULT createYBState();
	HRESULT createCBState();
	HRESULT createMBState();
};