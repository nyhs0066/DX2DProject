#pragma once
#include "myingamescene.h"
#include "mypausescene.h"
#include "mytitlescene.h"
#include "mygameoverscene.h"

class TestCase : public MyGameCore
{
private:
	MyScene* currentScene;
	MyScene* pauseScene;
	MyScene* titleScene;

	BOOL pauseFlag;

public:
	void sceneLoader();

	bool init();
	bool frame();
	bool render();
	bool release();
};