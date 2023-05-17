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
	rPaths.push_back(L"../../data/shapes/");

	LOAD_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");
	rPaths.push_back(L"../../data/sprite_set/test_sprites/");

	//UI textures and sprites : 4
	LOAD_TEXTURE(L"../../data/ui/UI_empty_list.png");
	LOAD_TEXTURE(L"../../data/ui/UI_plus0.png");
	LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
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
	//hit : 0
	MyEffect* newPreset = new MyEffect;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"sparkle.png", L"sparkle");
	newPreset->m_SPRect.fWH = { 75.0f, 75.0f };
	newPreset->m_BRect = BoundaryRect;
	newPreset->setTimeProperty(1.0f, 1.0f);
	ePresetList.push_back(newPreset);

	//bullet : 1
	newPreset = new MyProjectile;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_SPRect.fWH = { 10.0f, 10.0f };
	newPreset->m_BRect = BoundaryRect;
	newPreset->setTimeProperty(3.0f, 3.0f);
	ePresetList.push_back(newPreset);

	//create : 2
	newPreset = new MyEffect;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_BRect = BoundaryRect;
	newPreset->m_SPRect.fWH = { 30.0f, 30.0f };
	newPreset->setTimeProperty(1.0f, 1.0f);
	newPreset->m_color = { 0.0f, 1.0f, 0.0f, 0.2f };
	ePresetList.push_back(newPreset);
	ePresetList[1]->m_pCreateEPresets.push_back(ePresetList[2]);

	//destruct : 3
	newPreset = new MyEffect;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_BRect = BoundaryRect;
	newPreset->m_SPRect.fWH = { 30.0f, 30.0f };
	newPreset->setTimeProperty(1.0f, 1.0f);
	newPreset->m_color = { 1.0f, 0.0f, 0.0f, 0.2f };
	ePresetList.push_back(newPreset);
	ePresetList[1]->m_pDestructEPresets.push_back(ePresetList[3]);

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		49.5f, 49.5f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();
	dummy.m_fAttackSpeed = 20.0f;

	//pHitDummy Set
	pHitDummy = new MyObject2D;
	pRect = { 1000.0f, BoundaryRect.fWH.y - 100.0f, 100.0f, 100.0f };
	tRect = { 0.0f, 0.0f, 100.0f, 100.0f };
	pHitDummy->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, tRect, BoundaryRect);
	pHitDummy->init();
	pHitDummy->m_iMaxHitPoint = 100;
	pHitDummy->m_iHitPoint = 100;

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

	//timer Set
	timer = 0.0f;
	hitTimer = 0.0f;

	return true;
}

bool TestCase::frame()
{
	dummy.frame();
	mainCam.frame();
	BGObj.frame();
	BGObj.postFrame(mainCam.getCamRect());

	pHitDummy->frame();

	platForms->frame();
	platForms->postFrame(mainCam.getCamRect());

	cList.clear();
	space.getCollisionList(&dummy, cList);
	for (auto it : cList)
	{
		dummy.staticCollisionHandler(it, instRt);
	}

	dummy.postFrame(mainCam.getCamRect());

	MYRND_FRANGE(0.0f, 1.0f);
	if (MAININPUT.getKeyState(VK_LBUTTON))
	{
		timer += MAINTIMER.getOneFrameTimeF();
		if (timer > 1.0f / dummy.m_fAttackSpeed)
		{
			timer -= 1.0f / dummy.m_fAttackSpeed;

			MyEffect* newE = new MyProjectile;
			*newE = *ePresetList[1];
			newE->m_SPRect.pos = dummy.m_sup.getPosRect().pos;
			newE->setDirectionAndSpeed(dummy.m_sup.getDirection(), 250.0f, 0.0f);
			newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };

			effectList.push_back(newE);

			MyEffect* creE = new MyEffect;
			*creE = *(newE->m_pCreateEPresets[0]);
			creE->m_SPRect.pos = dummy.m_sup.getPosRect().pos;
			effectList.push_back(creE);
		}
	}

	for (it = effectList.begin(); it != effectList.end(); it++)
	{
		(*it)->update();
		if (!(*it)->m_LifeFlag)
		{
			cit = it;
			deleteList.push_back(cit);

			if ((*it)->m_fSpeed > 0.0f)
			{
				MyEffect* destE = new MyEffect;
				*destE = *((*it)->m_pDestructEPresets[0]);
				destE->m_SPRect = (*it)->m_SPRect;
				destE->m_SPRect.fWH = { 30.0f, 30.0f };

				effectList.push_back(destE);
			}
		}
		else
		{
			MyRect temp;
			if (MyCollision::rectToRect((*it)->m_CSRect, pHitDummy->getCollisionRect(), &temp))
			{
				cit = it;
				deleteList.push_back(cit);

				MyEffect* newE = new MyEffect;
				*newE = *ePresetList[0];
				newE->m_SPRect.pos = temp.getCpos();
				newE->m_color = { MYRND.getF(), 0.0f, 0.0f, 1.0f };

				effectList.push_back(newE);

				pHitDummy->m_iHitPoint -= (*it)->m_iDamage;

				if (pHitDummy->m_iHitPoint < 0) { pHitDummy->m_iHitPoint = pHitDummy->m_iMaxHitPoint; }

				hitTimer = 0.0f;
				pHitDummy->setColors({ 1.0f, (FLOAT)pHitDummy->m_iHitPoint / pHitDummy->m_iMaxHitPoint , 0.0f, 1.0f });
				pHitDummy->setShader(L"../../data/shader/mydefaultcollisionshader.txt");
			}
		}
	}


	for (const auto it : deleteList)
	{
		MyEffect* temp = *it;
		effectList.erase(it);	//이 과정에서 cit가 가리키고 있는 내용이 사라진다.
		delete temp;
		temp = nullptr;
	}
	deleteList.clear();

	pHitDummy->postFrame(mainCam.getCamRect());

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();
	platForms->render();

	pHitDummy->render();

	hitTimer += MAINTIMER.getOneFrameTimeF();
	if (hitTimer > FIXFRAMET)
	{
		pHitDummy->setColors({ 1.0f, 1.0f, 1.0f, 1.0f });
		pHitDummy->setShader(L"../../data/shader/mydefaultshader.txt");

		hitTimer -= FIXFRAMET;
	}

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		it->preRender(mainCam.getCamRect());
		MyEffect::g_pDrawObj->render();
	}

	return true;
}

bool TestCase::release()
{
	dummy.release();
	BGObj.release();
	platForms->release();
	pHitDummy->release();
	delete pHitDummy;
	pHitDummy = nullptr;

	for (std::list<MyEffect*>::iterator::value_type it : ePresetList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();
	return true;
}

GAME_RUN(Test_ApplyLifespanEffect, 1000, 1000)