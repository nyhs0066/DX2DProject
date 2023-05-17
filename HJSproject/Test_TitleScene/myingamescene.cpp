#include "myingamescene.h"

bool MyInGameScene::loadResource()
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
	LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
	rPaths.push_back(L"../../data/ui/");

	return true;
}

bool MyInGameScene::init()
{
	loadResource();

	//BG Set
	BGObj.create(rPaths[0] + L"mydefaultshader.txt", rPaths[1] + L"grid.png");
	BGObj.setBGdefault();
	BoundaryRect = BGObj.m_TRect;

	//space Partition
	space.maxDepth = 5;
	space.create(BoundaryRect);

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, BoundaryRect.fWH.y - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//UI Set
	pEmptyBar = new MyUserInterface;
	pEmptyBar->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_empty.png");
	MyRect texRt = pEmptyBar->m_TRect;
	pEmptyBar->setPosRect({ { 100.0f, 800.0f }, {140.0f, 18.0f} });
	pEmptyBar->setSprite(L"test_bar");

	pBar = new MyUIChargeBar;
	pBar->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_full.png");
	pBar->setPosRect({ { 100.0f, 800.0f },  {140.0f, 18.0f} });
	pBar->setTexRect(texRt);
	pBar->setSprite(L"test_bar");
	pBar->init();
	pBar->addChild(pEmptyBar);

	testUI.create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_popup_title.png");
	testUI.setPosRect({ (FLOAT)MyWindow::cWidth * 0.75f, (FLOAT)MyWindow::cHeight * 0.0f, (FLOAT)MyWindow::cWidth * 0.25f, (FLOAT)MyWindow::cHeight * 0.25f });
	testUI.partition(0.05f, 0.05f,
		0.05f, 0.05f,
		0.25f, 0.25f,
		0.4f, 0.4f);

	MyUserInterface* pUItemp = new MyUIButton;
	MyUserInterface* pTemp;

	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_plus_disable.png");
	pUItemp->setSprite(L"test_plus");
	MyVector2F UIPos = testUI.m_SPRect.pos + MyVector2F(10.0f, 10.0f);
	MyRect UIPRect = pUItemp->m_TRect;
	UIPRect.pos = UIPos;
	pUItemp->setPosRect(UIPRect);

	testUI.addChild(pUItemp);

	pUItemp = new MyUIListControl;
	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_empty_list.png");
	UIPRect = { 50.0f, 50.0f, 100.0f * 4 + 20.0f * 4, 120.0f };
	pUItemp->setPosRect(UIPRect);

	for (int i = 0; i < 3; i++)
	{
		pTemp = new MyUIButton;
		pTemp->create(L"../../data/shader/mydefaultshader.txt",
			L"../../data/ui/UI_plus_disable.png");
		pTemp->setSprite(L"test_plus");
		UIPRect = { 60.0f + 120.0f * i, 10.0f + 50.0f, 100.0f, 100.0f };
		pTemp->setPosRect(UIPRect);

		MyVector4F color;
		color.v[i] = 1.0f;
		color.v[3] = 1.0f;
		pTemp->setColors(color);

		pUItemp->addChild(pTemp);
	}

	testUI.addChild(pUItemp);


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
	dummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, BoundaryRect);
	dummy.init();
	dummy.m_fAttackSpeed = 20.0f;

	//pHitDummy Set
	pHitDummy = new MyObject2D;
	pRect = { 1000.0f, BoundaryRect.fWH.y - 100.0f, 100.0f, 100.0f };
	pHitDummy->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, BoundaryRect);
	pHitDummy->init();
	pHitDummy->m_iMaxHitPoint = 100;
	pHitDummy->m_iCurHitPoint = 100;

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

bool MyInGameScene::frame()
{
	testUI.frame();
	pBar->frame();
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
			newE->m_SPRect.pos = dummy.m_sup.m_SPRect.pos;
			newE->setDirectionAndSpeed(dummy.m_sup.getDirection(), 250.0f, 0.0f);
			newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };

			effectList.push_back(newE);

			MyEffect* creE = new MyEffect;
			*creE = *(newE->m_pCreateEPresets[0]);
			creE->m_SPRect.pos = dummy.m_sup.m_SPRect.pos;
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
			if (MyCollision::rectToRect((*it)->m_CSRect, pHitDummy->getCSRect(), &temp))
			{
				cit = it;
				deleteList.push_back(cit);

				MyEffect* newE = new MyEffect;
				*newE = *ePresetList[0];
				newE->m_SPRect.pos = temp.getCpos();
				newE->m_color = { MYRND.getF(), 0.0f, 0.0f, 1.0f };

				effectList.push_back(newE);

				pHitDummy->m_iCurHitPoint -= (*it)->m_iDamage;

				if (pHitDummy->m_iCurHitPoint < 0) { pHitDummy->m_iCurHitPoint = pHitDummy->m_iMaxHitPoint; }

				hitTimer = 0.0f;
				pHitDummy->setColors({ 1.0f, (FLOAT)pHitDummy->m_iCurHitPoint / pHitDummy->m_iMaxHitPoint , 0.0f, 1.0f });
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

bool MyInGameScene::render()
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

	testUI.render();
	pBar->render();

	wstring mpt = std::to_wstring(MAININPUT.getMousePt().x) + L" " + std::to_wstring(MAININPUT.getMousePt().y);
	TEXT_WRITER.drawT(mpt, (FLOAT)MAININPUT.getMousePt().x, (FLOAT)MAININPUT.getMousePt().y + 50.0f, { 1.0f, 0.0f, 0.0f, 1.0f });

	return true;
}

bool MyInGameScene::release()
{
	dummy.release();
	BGObj.release();

	for (std::list<MyEffect*>::iterator::value_type it : ePresetList)
	{
		delete it;
		it = nullptr;
	}
	ePresetList.clear();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	if (pHitDummy) { pHitDummy->release(); delete pHitDummy; pHitDummy = nullptr; }
	if (platForms) { platForms->release(); delete platForms; platForms = nullptr;}
	if (pBar) { pBar->release(); delete pBar; pBar = nullptr; }
	testUI.release();

	rPaths.clear();
	space.clear();
	cList.clear();

	return true;
}
