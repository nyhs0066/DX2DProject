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
	DRAWTEXT(L"»£ªß¿Ã", 50, 50);
	TEXT_WRITER.drawTLayout();

	return true;
}

bool TestCase::release()
{
	return true;
}

GAME_RUN(My First Library Application, 600, 600)