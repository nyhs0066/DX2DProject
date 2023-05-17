#pragma once
#include "myingamescene.h"
#include "mypausescene.h"
#include "mytitlescene.h"
#include "mygameoverscene.h"

class TestCase : public MyGameCore
{
private:
	MyScene* currentScene;
	MyScene* nextScene;
	MyScene* prevScene;
	MyScene* pauseScene;
	MyScene* titleScene;

	MyObject2D fadeObj;
	FLOAT deltaSpeed;
	FLOAT speed;
	FLOAT velocity;

	BOOL sceneChangeStartFlag;
	BOOL sceneChangeEndFlag;

	BOOL pauseFlag;
	BOOL gameEndFlag;

public:
	void sceneLoader();

	bool init();
	bool frame();
	bool render();
	bool release();
};