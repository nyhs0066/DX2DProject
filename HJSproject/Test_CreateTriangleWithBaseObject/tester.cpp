#include "tester.h"

bool TestCase::init()
{
	test.create(L"triangleshader.txt");
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