#include "tester.h"

bool TestCase::init()
{
	test.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/1.jpg");
	return true;
}

bool TestCase::frame()
{
	test.frame();
	return true;
}

bool TestCase::render()
{
	test.render();
	return true;
}

bool TestCase::release()
{
	test.release();
	return true;
}

GAME_RUN(My First Library Application, 600, 600)