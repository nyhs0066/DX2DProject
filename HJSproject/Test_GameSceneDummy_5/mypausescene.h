#pragma once
#include "myscenemanager.h"

class MyPauseScene : public MyScene
{
public:
	MyBackGroundObject pauseBGObj;
	std::shared_ptr<MyUserInterface> pBackTitleButton;

	bool loadResource();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};