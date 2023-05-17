#include "tester.h"

bool TestCase::init()
{
	MyRect pRect = { {(FLOAT)MyWindow::cWidth / 2 - 50.0f, (FLOAT)MyWindow::cHeight / 2 - 50.0f}, {100.0f, 100.0f} };
	MyRect tRect = { {0.0f, 0.0f}, {380.0f, 400.0f} };

	playerObj.create(L"myalphatextureshader.txt",
		L"../../data/freedinosprite/Idle1.png",
		L"../../data/freedinosprite/Idle1.png",
		pRect, tRect);
	playerObj.init();

	timer = 0.0f;
	counter = 0;

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

	return true;
}

bool TestCase::frame()
{
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

GAME_RUN(Object Animation 1, 600, 600)