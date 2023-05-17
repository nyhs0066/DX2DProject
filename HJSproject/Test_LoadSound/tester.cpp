#include "tester.h"

bool TestCase::init()
{
	if (test.create()) { return false; };
	test.init();

	if (test.loadSound("../../data/sound/FlameThrower_Fire_Loop_Stereo.WAV"))
	{
		return false;
	}

	return true;
}

bool TestCase::frame()
{
	test.frame();

	if (MAININPUT.getKeyState('Q') == KEY_DOWN) { test.playEffect(); }

	return true;
}

bool TestCase::render()
{
	//unused
	//test.render();
	return true;
}

bool TestCase::release()
{
	test.release();
	return true;
}

GAME_RUN(Load Sound, 600, 600)