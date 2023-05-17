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

	return true;
}

bool TestCase::frame()
{
	mapObj.frame();
	playerObj.frame();
	return true;
}

bool TestCase::render()
{
	mapObj.render();
	playerObj.render();
	return true;
}

bool TestCase::release()
{
	mapObj.release();
	playerObj.release();
	return true;
}

GAME_RUN(Move Object, 192*3, 232*3)