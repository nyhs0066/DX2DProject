#include "tester.h"

bool TestCase::init()
{
	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Height;

	space.maxDepth = 5;
	space.create({ 0.0f, 0.0f }, { bW, bH });

	BoundaryRect = space.getBoundary();

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		99.0f, 99.0f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(L"../../data/shader/myalphatextureshader.txt", L"../../data/shapes/Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();

	//BG Set
	BGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/texture/010.jpg",
		pRect, tRect, BoundaryRect);
	BGObj.setBGdefault();

	//ball set
	for (int i = 0; i < 100; i++)
	{
		MyBall* newE = new MyBall;
		newE->create(BoundaryRect);
		newE->init();

		ballList.push_back(newE);
	}

	//Cam set
	mainCam.setBoundaryRect(BoundaryRect);
	mainCam.setFollowTarget(&dummy);

	return true;
}

bool TestCase::frame()
{
	dummy.frame();
	mainCam.frame();
	BGObj.frame();
	BGObj.postFrame(mainCam.getCamRect());

	csList.clear();
	/*space.resetAllDynamicList();

	for (std::list<MyBall*>::iterator::value_type it : ballList)
	{
		it->frame();
		space.addDynamicObject(it);
		it->postFrame(mainCam.getCamRect());
	}

	space.getCollisionList(&dummy, csList);*/

	for (std::list<MyBall*>::iterator::value_type it : ballList)
	{
		it->frame();
		//space.addDynamicObject(it);

		if (MyCollision::rectToRect(dummy.getCollisionRect(), it->getCollisionRect()))
		{
			csList.push_back(it);
		}
		it->postFrame(mainCam.getCamRect());
	}

	COLLISION_PLANE cp = MYCP_NONE;
	bool cFlag = false;

	cFlag |= dummy.boundaryCheck();
	if (!cFlag) { dummy.setAerial(); }

	dummy.postFrame(mainCam.getCamRect());

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();
	for (std::list<MyBall*>::iterator::value_type it : ballList)
	{
		it->render();
	}

	TEXT_WRITER.drawT(std::to_wstring(csList.size()), 400, 400);
	
	return true;
}

bool TestCase::release()
{
	dummy.release();
	BGObj.release();
	for (std::list<MyBall*>::iterator::value_type it : ballList)
	{
		delete it;
		it = nullptr;
	}
	ballList.clear();

	return true;
}

GAME_RUN(Test_RotateObject, 800, 800)