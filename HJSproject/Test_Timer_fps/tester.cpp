#include "tester.h"

bool TestCase::init()
{
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
	return true;
}

GAME_RUN(My First Library Application, 600, 600)