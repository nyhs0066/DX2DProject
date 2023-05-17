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

	std::unique_ptr<MyScene> gOverScene = std::make_unique<MyGameOverScene>();
	gOverScene->wszSceneName = L"GameOver";
	SCENE_MANAGER.addScene(L"GameOver", gOverScene);
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

	fadeObj.create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/background/black.png");
	fadeObj.setPosRect({ -1000.0f, 0.0f, 1000.0f, 1000.0f });
	deltaSpeed = 1500.0f;
	speed = 0.0f;
	velocity = 0.0f;

	sceneChangeStartFlag = FALSE;
	sceneChangeEndFlag = TRUE;

	pauseFlag = FALSE;
	gameEndFlag = FALSE;

	return true;
}

bool TestCase::frame()
{
	if(currentScene->wszSceneName == L"InGame")
	{
		if (MAININPUT.getKeyState(VK_ESCAPE) == KEY_DOWN) { pauseFlag = !pauseFlag; }
	}
	else { pauseFlag = FALSE; }

	if (currentScene->bSceneFlag)
	{
		sceneChangeStartFlag = TRUE;
		if (currentScene->wszSceneName == L"Title")
		{
			if (currentScene->bSceneFlag == 1)
			{
				nextScene = SCENE_MANAGER.getScene(L"InGame");
				prevScene = currentScene;
			}
		}
		else if (currentScene->wszSceneName == L"InGame")
		{
			if (currentScene->bSceneFlag == 1)
			{
				nextScene = SCENE_MANAGER.getScene(L"GameOver");
				prevScene = currentScene;
			}
		}
		else if (currentScene->wszSceneName == L"GameOver")
		{
			if (currentScene->bSceneFlag == 1)
			{
				nextScene = SCENE_MANAGER.getScene(L"Title");
				prevScene = currentScene;
			}
			else if (currentScene->bSceneFlag == 2)
			{
				nextScene = SCENE_MANAGER.getScene(L"InGame");
				prevScene = currentScene;
			}
			else if (currentScene->bSceneFlag == 3)
			{
				gameEndFlag = TRUE;
				currentScene->release();
				pauseScene->release();
				PostQuitMessage(0);
			}
		}
	}

	if (!gameEndFlag)
	{
		if (pauseScene->bSceneFlag == 1)
		{
			currentScene->release();
			currentScene = SCENE_MANAGER.getScene(L"Title");
			pauseScene->bSceneFlag = 0;
			currentScene->init();
		}

		if (pauseFlag) { pauseScene->frame(); }
		else
		{
			if (!sceneChangeStartFlag) { currentScene->frame(); }

			if(sceneChangeStartFlag)
			{
				speed += deltaSpeed * MAINTIMER.getOneFrameTimeF();
				velocity += speed * MAINTIMER.getOneFrameTimeF();
				fadeObj.m_SPRect.pos.x += velocity * MAINTIMER.getOneFrameTimeF();

				if (fadeObj.m_SPRect.pos.x > 0.0f)
				{
					fadeObj.m_SPRect.pos.x = 0.0f;
					currentScene = nextScene;
					currentScene->init();

					prevScene->release();
					nextScene = nullptr;
					prevScene = nullptr;

					sceneChangeStartFlag = FALSE;
					sceneChangeEndFlag = FALSE;

					velocity = 0.0f;
				}

				fadeObj.postFrame();
			}

			if (!sceneChangeEndFlag)
			{
				speed += deltaSpeed * MAINTIMER.getOneFrameTimeF();
				velocity += speed * MAINTIMER.getOneFrameTimeF();
				fadeObj.m_SPRect.pos.x += velocity * MAINTIMER.getOneFrameTimeF();

				if (fadeObj.m_SPRect.pos.x > 1000.0f)
				{
					fadeObj.m_SPRect.pos.x = -1000.0f;

					sceneChangeEndFlag = TRUE;
					velocity = 0.0f;
				}

				fadeObj.postFrame();
			}
		}
	}

	return true;
}

bool TestCase::render()
{
	if (!gameEndFlag)
	{
		currentScene->render();
		if ((sceneChangeStartFlag) || (!sceneChangeEndFlag)) { fadeObj.render(); }

		if (pauseFlag) { pauseScene->render(); }
	}
	return true;
}

bool TestCase::release()
{
	currentScene = nullptr;
	pauseScene = nullptr;
	return true;
}

GAME_RUN(Test_GameSceneDummy_0, 1000, 1000)