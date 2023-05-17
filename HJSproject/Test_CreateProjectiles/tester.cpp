#include "tester.h"

bool TestCase::loadResource()
{
	//shaders : 0
	LOAD_SHADER_DIR(L"../../data/shader/");
	rPaths.push_back(L"../../data/shader/");

	//map textures : 1
	LOAD_TEXTURE_DIR(L"../../data/background/");
	rPaths.push_back(L"../../data/background/");

	//obj textures and sprites : 2 3
	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	rPaths.push_back(L"../../data/shapes/");

	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");
	rPaths.push_back(L"../../data/sprite_set/test_sprites/");

	//UI textures and sprites : 4
	LOAD_TEXTURE(L"../../data/ui/UI_empty_list.png");
	LOAD_TEXTURE(L"../../data/ui/UI_plus0.png");
	LOAD_MT_SPRITE(L"../../data/ui/test_UI_list.txt");
	rPaths.push_back(L"../../data/ui/");

	return true;
}

bool TestCase::init()
{
	loadResource();

	//BG Set
	BGObj.create(rPaths[0] + L"mydefaultshader.txt", rPaths[1] + L"grid.png");
	BGObj.setBGdefault();

	BoundaryRect = BGObj.getTexRect();

	space.maxDepth = 5;
	space.create(BoundaryRect);

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, BoundaryRect.fWH.y - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//effect preset part
	preset1.create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"sparkle.png", L"sparkle");
	preset1.m_pDrawing->setBoundRect(BoundaryRect);

	preset2.create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	preset2.m_pDrawing->setBoundRect(BoundaryRect);

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		49.5f, 49.5f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();
	
	//map obj set
	platForms = new MyTilePlatform;

	MyMapObject* platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 2.0f + 50.0f , BoundaryRect.fWH.y - 50.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect, mainCam.getCamRect());

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 2.0f + i * 50.0f , BoundaryRect.fWH.y - 50.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	space.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 1.5f + 50.0f , BoundaryRect.fWH.y - 250.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect, mainCam.getCamRect());
	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 1.5f + i * 50.0f , BoundaryRect.fWH.y - 250.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	space.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 3.0f + 50.0f , BoundaryRect.fWH.y - 150.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect, mainCam.getCamRect());
	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 3.0f + i * 50.0f , BoundaryRect.fWH.y - 150.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	space.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 4.0f + 50.0f , BoundaryRect.fWH.y - 350.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect, mainCam.getCamRect());
	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 4.0f + i * 50.0f , BoundaryRect.fWH.y - 350.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	space.addStaticObject(platForm);

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

	platForms->frame();
	platForms->postFrame(mainCam.getCamRect());

	cList.clear();
	space.getCollisionList(&dummy, cList);
	for (auto it : cList)
	{
		dummy.staticCollisionHandler(it, instRt);
	}

	dummy.postFrame(mainCam.getCamRect());

	if (MAININPUT.getKeyState(VK_LBUTTON) == KEY_HOLD)
	{
		MyRect temp;
		MyProjectile* newE = new MyProjectile;
		temp.pos = dummy.m_sup.getPosRect().pos;
		temp.fWH = { 10.0f, 10.0f };
		newE->setProjectileProperty(&preset2, temp, 3.0f, 3.0f, dummy.m_sup.getDirection(),
			250.0f, 1);

		effectList.push_back(newE);
	}

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

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();
	platForms->render();
	
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
	platForms->release();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	return true;
}

GAME_RUN(Test_CreateProjectile, 800, 800)