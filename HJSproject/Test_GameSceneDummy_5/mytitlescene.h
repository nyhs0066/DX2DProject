#pragma once
#include "myscenemanager.h"

class MyTitleScene : public MyScene
{
public:
	MyBackGroundObject BG;

	MyObject2D p1;
	MyObject2D a1;
	MyObject2D p2;
	MyObject2D e1;
	MyObject2D r1;
	MyObject2D w1;
	MyObject2D a2;
	MyObject2D r2;
	MyObject2D s1;

	std::shared_ptr<MyUserInterface> pPlayButton;
	//std::shared_ptr<MyUserInterface> pSettingButton;

	MySound* titleBGM;
	MySound* startbuttonpush;

	MyTitleScene();
	~MyTitleScene();

	bool init();
	bool frame();
	bool render();
	bool release();
};