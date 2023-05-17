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

	std::unique_ptr<MyScene> gClearScene = std::make_unique<MyGameClearScene>();
	gClearScene->wszSceneName = L"Clear";
	SCENE_MANAGER.addScene(L"Clear", gClearScene);
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
	fadeObj.setPosRect({ (FLOAT)(-MyWindow::cWidth), 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight});
	deltaSpeed = 2000.0f;
	speed = 0.0f;
	velocity = 0.0f;

	sceneChangeStartFlag = FALSE;
	sceneChangeEndFlag = TRUE;

	pauseFlag = FALSE;
	gameEndFlag = FALSE;

	return true;
}

//bSceneFlag ¼ø¼­ : 0 idle / 1 title / 2 in game / 3 gameover / 4 clear / 5 exit
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

		switch (currentScene->bSceneFlag)
		{
		case 1: 
			nextScene = SCENE_MANAGER.getScene(L"Title");
			prevScene = currentScene;
			break;
		case 2:
			nextScene = SCENE_MANAGER.getScene(L"InGame");
			prevScene = currentScene;
			break;
		case 3 :
			nextScene = SCENE_MANAGER.getScene(L"GameOver");
			prevScene = currentScene;
			break;
		case 4 :
			nextScene = SCENE_MANAGER.getScene(L"Clear");
			prevScene = currentScene;
			break;
		case 5 :
			gameEndFlag = TRUE;
			currentScene->release();
			pauseScene->release();
			PostQuitMessage(0);
			break;
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

				if (fadeObj.m_SPRect.pos.x > MyWindow::cWidth)
				{
					fadeObj.m_SPRect.pos.x = -MyWindow::cWidth;

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
	nextScene = nullptr;
	prevScene = nullptr;
	titleScene = nullptr;

	return true;
}

GAME_RUN(My First Game, 1440, 1024)