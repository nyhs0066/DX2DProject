#pragma once
#include "myscenemanager.h"

class MyGameOverScene : public MyScene
{
	//MyBackGroundObject gameOverBGObj;
	std::shared_ptr<MyUserInterface> pButtonGroup;

	bool loadResource();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};