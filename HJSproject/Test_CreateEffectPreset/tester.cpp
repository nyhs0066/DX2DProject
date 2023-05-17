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

	//effect preset part
	preset1.createEffectPreset(L"../../data/shader/myalphatextureshader.txt",
		L"../../data/sprite_set/test_sprites/sparkle.png", L"sparkle");
	preset1.m_pDrawing->setBoundRect(BoundaryRect);

	//effect create
	for (int i = 0; i < 100; i++)
	{
		FLOAT fRand = MYRND.getF(0.0f, 250.0f);

		MyEffect* newE = new MyEffect;
		newE->m_pEPreset = &preset1;
		newE->init();
		newE->setTimeProperty(10.0f + MYRND.getF(0.0f, 10.0f), 2.0f + MYRND.getF(0.0f, 2.0f));
		newE->m_SPRect.pos = { MYRND.getF(0.0f, bW), MYRND.getF(0.0f, bH) };
		newE->m_SPRect.fWH = { 50.0f + fRand, 50.0f + fRand };

		effectList.push_back(newE);
	}

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

	for (it = effectList.begin(); it != effectList.end();)
	{
		if (!(*it)->update())
		{
			cit = it;
			it++;
			delete (*cit);
			effectList.erase(cit);
		}
		else { it++; }
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

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		it->preRender(mainCam.getCamRect());
		it->m_pEPreset->m_pDrawing->render();
	}
	
	return true;
}

bool TestCase::release()
{
	dummy.release();
	BGObj.release();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	return true;
}

GAME_RUN(Test_RotateObject, 800, 800)