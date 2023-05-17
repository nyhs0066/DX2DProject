#include "tester.h"

bool TestCase::init()
{
	mapObj.create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/arkanoid/nes_arkanoid_fields.png",
		0, 0, 192, 232);
	mapObj.init();


	playerObj.create(L"../../data/shader/mydefaultmaskshader.txt",
		L"../../data/arkanoid/nes_arkanoid_vaus.png",
		L"../../data/arkanoid/nes_arkanoid_vaus_mask.png",
		{ {(FLOAT)MyWindow::cWidth / 2 - 16*3, (FLOAT)MyWindow::cHeight * 13 / 15}, {32*3, 8*3} },
		{ {0, 0}, {32, 8} });
	playerObj.init();

	for (int i = 0; i < 10; i++)
	{
		MyDynamicObject2F* newE = new MyDynamicObject2F;

		DynamicObjectList.push_back(newE);
		DynamicObjectList[i]->create(L"../../data/shader/mydefaultmaskshader.txt",
			L"../../data/arkanoid/nes_arkanoid_vaus.png",
			L"../../data/arkanoid/nes_arkanoid_vaus_mask.png",
			{ {(FLOAT)MyWindow::cWidth / 2 - 2.5f * 3, (FLOAT)MyWindow::cHeight / 2}, {5 * 3, 4 * 3} },
			{ {40, 0}, {5, 4} });
		DynamicObjectList[i]->init();
	}

	return true;
}

bool TestCase::frame()
{
	mapObj.frame();
	playerObj.frame();

	for (int i = 0; i < 10; i++) { DynamicObjectList[i]->frame(); }
	
	return true;
}

bool TestCase::render()
{
	mapObj.render();
	playerObj.render();

	for (int i = 0; i < 10; i++) { DynamicObjectList[i]->render(); }
	return true;
}

bool TestCase::release()
{
	mapObj.release();
	playerObj.release();

	for (int i = 0; i < 10; i++)
	{
		DynamicObjectList[i]->release();
		delete DynamicObjectList[i];
		DynamicObjectList[i] = nullptr;
	}

	DynamicObjectList.clear();
	return true;
}

GAME_RUN(Move Object, 192*3, 232*3)