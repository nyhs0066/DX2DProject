#include "tester.h"

bool TestCase::init()
{
	//verified
	/*SOUND_MANAGER.loadDir(L"../../data/");
	SOUND_MANAGER.getSplitName(L"D:/KCGAstudyRepository/data/freedinosprite/Idle1.png");*/
	SOUND_MANAGER.init();

	pTest = LOAD_SOUND(L"../../data/sound/FlameThrower_Fire_Loop_Stereo.WAV");

	return true;
}

bool TestCase::frame()
{
	SOUND_MANAGER.frame();
	pTest->frame();

	if (MAININPUT.getKeyState('Q') == KEY_DOWN) { pTest->playEffect(); }

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
	SOUND_MANAGER.release();
	return true;
}

GAME_RUN(Load Sound, 600, 600)