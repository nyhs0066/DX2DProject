#pragma once
#include "myscenemanager.h"

class MyPauseScene : public MyScene
{
public:
	MyBackGroundObject pauseBGObj;

	bool loadResource();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};