#include "tester.h"

void TestCase::sceneLoader()
{
	std::unique_ptr<MyScene> inGameScene = std::make_unique<MyInGameScene>();
	SCENE_MANAGER.addScene(L"InGame", inGameScene);

	std::unique_ptr<MyScene> pScene = std::make_unique<MyPauseScene>();
	SCENE_MANAGER.addScene(L"Pause", pScene);
}

bool TestCase::init()
{
	sceneLoader();

	currentScene = SCENE_MANAGER.getScene(L"InGame");
	pauseScene = SCENE_MANAGER.getScene(L"Pause");

	currentScene->init();
	pauseScene->init();

	pauseFlag = FALSE;

	return true;
}

bool TestCase::frame()
{
	if (MAININPUT.getKeyState(VK_ESCAPE) == KEY_DOWN) { pauseFlag = !pauseFlag; }

	if (pauseFlag) { pauseScene->frame(); }
	else { currentScene->frame(); }

	return true;
}

bool TestCase::render()
{
	currentScene->render();

	if (pauseFlag) { pauseScene->render(); }

	return true;
}

bool TestCase::release()
{
	currentScene = nullptr;
	pauseScene = nullptr;
	return true;
}

GAME_RUN(Test_PauseScene_1, 1000, 1000)