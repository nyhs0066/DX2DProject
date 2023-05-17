#include "tester.h"

BOOL TestCase::run()
{
	init();

	return 0;
}

bool TestCase::init()
{
	if (FAILED(MyDxDeviceManager::getInstance().create())) { return false; };
	return true;
}

bool TestCase::frame()
{
	return true;
}

bool TestCase::render()
{
	return true;
}

bool TestCase::release()
{
	MyDxDeviceManager::getInstance().release();
	return true;
}

GAME_RUN(My First Library Application, 600, 600)