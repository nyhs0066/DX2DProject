#include "tester.h"

bool TestCase::init()
{
	playerObj.create(L"../../data/shader/mydefaultmaskshader.txt",
		L"../../data/freedinosprite/Idle0.png",
		L"../../data/freedinosprite/Idle0.png",
		{ {(FLOAT)MyWindow::cWidth / 2 - 50.0f, (FLOAT)MyWindow::cHeight / 2 - 50.0f, 0.0f}, {100.0f, 100.0f, 0.0f} },
		{ {0.0f, 0.0f, 0.0f}, {380.0f, 400.0f, 0.0f} });
	playerObj.init();

	timer = 0.0f;
	counter = 0;

	spriteName.push_back(L"../../data/freedinosprite/Idle0.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle1.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle2.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle3.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle4.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle5.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle6.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle7.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle8.png");
	spriteName.push_back(L"../../data/freedinosprite/Idle9.png");

	return true;
}

bool TestCase::frame()
{
	timer += MAINTIMER.getOneFrameTimeF();

	if (timer > 0.1f) { timer = 0.0f; counter++; }

	wstring temp = std::to_wstring(timer) + L"\n";

	playerObj.setTexture(spriteName[counter % 10].c_str());
	playerObj.setMaskTexture(spriteName[counter % 10].c_str());

	playerObj.frame();
	
	return true;
}

bool TestCase::render()
{
	playerObj.render();

	return true;
}

bool TestCase::release()
{
	playerObj.release();
	return true;
}

GAME_RUN(Object Collision Detection, 600, 600)