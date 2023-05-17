#include "tester.h"

bool TestCase::init()
{
	//sprite load
	wstring fileName;
	playerObj.stateSpriteSet.push_back(vector<wstring>());
	for (int i = 0; i < 10; i++)
	{
		fileName = L"../../data/freedinosprite/Idle" + std::to_wstring(i) + L".png";
		playerObj.stateSpriteSet[0].push_back(fileName.c_str());
	}

	playerObj.stateSpriteSet.push_back(vector<wstring>());
	for (int i = 0; i < 10; i++)
	{
		fileName = L"../../data/freedinosprite/Walk" + std::to_wstring(i) + L".png";
		playerObj.stateSpriteSet[1].push_back(fileName.c_str());
	}

	playerObj.stateSpriteSet.push_back(vector<wstring>());
	for (int i = 0; i < 4; i++)
	{
		fileName = L"../../data/freedinosprite/JumpUp" + std::to_wstring(i) + L".png";
		playerObj.stateSpriteSet[2].push_back(fileName.c_str());
	}

	//background set
	BGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/FreeTileset/BG/BG.png");
	BGObj.init();

	//player Set
	MyRect pRect = { {(FLOAT)MyWindow::cWidth / 2 - 75.0f, (FLOAT)MyWindow::cHeight * 3 / 4 - 50.0f}, {150.0f, 100.0f} };
	MyRect tRect = { {0.0f, 0.0f}, {600.0f, 400.0f} };

	playerObj.create(L"myalphatextureshader.txt",
		L"../../data/freedinosprite/Idle0.png",
		L"../../data/freedinosprite/Idle0.png",
		pRect, tRect);
	playerObj.init();

	return true;
}

bool TestCase::frame()
{
	BGObj.frame();
	playerObj.frame();
	return true;
}

bool TestCase::render()
{
	BGObj.render();
	playerObj.render();

	return true;
}

bool TestCase::release()
{
	playerObj.release();
	BGObj.release();
	return true;
}

GAME_RUN(Object Animation 3, 800, 600)