#pragma once
#include "myscenemanager.h"

class MyTitleScene : public MyScene
{
public:
	MyBackGroundObject BG;

	std::shared_ptr<MyUserInterface> pPlayButton;
	std::shared_ptr<MyUserInterface> pSettingButton;

	MyTitleScene();
	~MyTitleScene();

	bool init();
	bool frame();
	bool render();
	bool release();
};