#include "tester.h"

void TestCase::sceneLoader()
{
	std::unique_ptr<MyScene> tScene = std::make_unique<MyTitleScene>();
	tScene->wszSceneName = L"Title";
	SCENE_MANAGER.addScene(L"Title", tScene);

	std::unique_ptr<MyScene> iGScene = std::make_unique<MyInGameScene>();
	iGScene->wszSceneName = L"InGame";
	SCENE_MANAGER.addScene(L"InGame", iGScene);

	std::unique_ptr<MyScene> pScene = std::make_unique<MyPauseScene>();
	pScene->wszSceneName = L"Pause";
	SCENE_MANAGER.addScene(L"Pause", pScene);
}

bool TestCase::init()
{
	sceneLoader();

	currentScene = SCENE_MANAGER.getScene(L"Title");
	currentScene->bSceneFlag = 0;

	pauseScene = SCENE_MANAGER.getScene(L"Pause");
	titleScene = SCENE_MANAGER.getScene(L"Title");

	currentScene->init();
	pauseScene->init();

	pauseFlag = FALSE;

	return true;
}

bool TestCase::frame()
{
	if(currentScene->wszSceneName != L"Title")
	{
		if (MAININPUT.getKeyState(VK_ESCAPE) == KEY_DOWN) { pauseFlag = !pauseFlag; }
	}

	if ((currentScene->wszSceneName == L"Title") && currentScene->bSceneFlag == 1)
	{
		currentScene->release();
		currentScene = SCENE_MANAGER.getScene(L"InGame");
		currentScene->bSceneFlag = 0;
		currentScene->init();
	}

	if (pauseScene->bSceneFlag == 1)
	{
		currentScene->release();
		currentScene = SCENE_MANAGER.getScene(L"Title");
		pauseScene->bSceneFlag = 0;
		pauseFlag = !pauseFlag;
		currentScene->bSceneFlag = 0;
		currentScene->init();
	}

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

GAME_RUN(Test_TitleScene, 1000, 1000)