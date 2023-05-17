#pragma once
#include "myscenemanager.h"

class MyGameOverScene : public MyScene
{
	MyBackGroundObject gameOverBGObj;
	std::shared_ptr<MyUserInterface> pButtonGroup;

	MyObject2D g1;
	MyObject2D a1;
	MyObject2D m1;
	MyObject2D e1;
	MyObject2D o1;
	MyObject2D v1;
	MyObject2D e2;
	MyObject2D r1;

	MySound* gameoverBGM;

	bool loadResource();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};