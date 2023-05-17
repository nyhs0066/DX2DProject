#include "tester.h"

bool TestCase::init()
{
	LOAD_MT_SPRITE(L"../../data/freedinosprite/freedinospriteinfo.txt");

	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Height;

	BoundaryRect.pos = { 0.0f, 0.0f };
	BoundaryRect.fWH = { bW, bH };

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		140.0f, 100.0f);
	MyRect tRect(0.0f, 0.0f, 680.0f, 472.0f);
	/*dummy.create(L"../../data/shader/myalphatextureshader.txt", L"../../data/shapes/Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();*/
	test.create(L"../../data/shader/myalphatextureshader.txt", L"../../data/freedinosprite/Idle0.png",
		pRect, tRect, BoundaryRect);
	test.init();
	test.addSprite(L"dino_idle");
	test.addSprite(L"dino_walk");
	test.addSprite(L"dino_jump_up");

	//BG Set
	BGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/texture/010.jpg",
		pRect, tRect, BoundaryRect);
	BGObj.setBGdefault();

	//Cam set
	mainCam.setBoundaryRect(BoundaryRect);
	//mainCam.setFollowTarget(&dummy);
	mainCam.setFollowTarget(&test);

	return true;
}

bool TestCase::frame()
{
	//dummy.frame();
	test.frame();
	mainCam.frame();
	BGObj.frame();
	BGObj.postFrame(mainCam.getCamRect());

	/*COLLISION_PLANE cp = MYCP_NONE;
	bool cFlag = false;

	cFlag |= dummy.boundaryCheck();
	if (!cFlag) { dummy.setAerial(); }

	dummy.postFrame(mainCam.getCamRect());*/

	test.postFrame(mainCam.getCamRect());

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	test.render();
	//dummy.render();
	
	return true;
}

bool TestCase::release()
{
	//dummy.release();
	test.release();
	BGObj.release();

	/*unused
	test.release();
	mainCam.release();*/

	return true;
}

GAME_RUN(Test_ObjectAnimationWithSprite, 800, 800)