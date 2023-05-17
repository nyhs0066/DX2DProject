#include "tester.h"

bool TestCase::init()
{
	SHADER_MANAGER.init();
	LOAD_SHADER(L"../../data/shader/mydefaultshader.txt");
	return true;
}

bool TestCase::frame()
{
	SHADER_MANAGER.frame();
	return true;
}

bool TestCase::render()
{
	SHADER_MANAGER.render();
	return true;
}

bool TestCase::release()
{
	SHADER_MANAGER.release();
	return true;
}

GAME_RUN(My First Library Application, 600, 600)