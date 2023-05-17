#pragma once
#include "myscenemanager.h"

class MyGameClearScene : public MyScene
{
	MyBackGroundObject gameClearBGObj;
	std::shared_ptr<MyUserInterface> pButtonGroup;

	MyObject2D c1;
	MyObject2D l1;
	MyObject2D e1;
	MyObject2D a1;
	MyObject2D r1;

	MySound* gameClearBGM;

	bool loadResource();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};