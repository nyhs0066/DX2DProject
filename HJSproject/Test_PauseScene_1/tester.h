#pragma once
#include "myingamescene.h"
#include "mypausescene.h"

class TestCase : public MyGameCore
{
private:
	MyScene* currentScene;
	MyScene* pauseScene;

	BOOL pauseFlag;

public:
	void sceneLoader();

	bool init();
	bool frame();
	bool render();
	bool release();
};