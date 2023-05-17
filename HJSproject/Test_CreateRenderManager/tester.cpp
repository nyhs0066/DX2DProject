#include "tester.h"

bool TestCase::init()
{
	if (FAILED(MyDxDeviceManager::getInstance().create())) { return false; }
	MyDxDeviceManager::getInstance().init();

	if (FAILED(MyRenderManager::getInstance().create())) { return false; }
	MyRenderManager::getInstance().init();

	return true;
}

bool TestCase::frame()
{
	return true;
}

bool TestCase::render()
{
	PRE_RENDER;

	//TO DO

	POST_RENDER;
	return true;
}

bool TestCase::release()
{
	MyRenderManager::getInstance().release();
	MyDxDeviceManager::getInstance().release();
	return true;
}

BOOL TestCase::run()
{
	if (!init()) { return false; }

	BOOL runFlag = true;

	while (runFlag)
	{
		if (!MyWindow::run()) { runFlag = false; }
		else
		{
			if (!frame() || !render()) { runFlag = false; }
		}
	}

	return runFlag;
}

GAME_RUN(My First Library Application, 600, 600)