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
	MYSPACE.maxDepth = 3;
	MYSPACE.create(BoundaryRect);

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, BoundaryRect.fWH.y - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//UI Set
	pEmptyBar = new MyUserInterface;
	pEmptyBar->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_empty.png");
	MyExRect texRt = pEmptyBar->m_TRect;
	pEmptyBar->setPosRect({ { 100.0f, 800.0f }, {140.0f, 18.0f} });
	pEmptyBar->setSprite(L"test_bar");

	pBar = new MyUIChargeBar;
	pBar->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_full.png");
	pBar->setPosRect({ { 100.0f, 800.0f },  {140.0f, 18.0f} });
	pBar->setTexRect(texRt);
	pBar->setSprite(L"test_bar");
	pBar->init();
	pBar->addChild(pEmptyBar);

	/*pTestUI = new MyUIDialog;
	pTestUI->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_popup_title.png");
	pTestUI->setPosRect({ (FLOAT)MyWindow::cWidth * 0.75f, (FLOAT)MyWindow::cHeight * 0.0f, (FLOAT)MyWindow::cWidth * 0.25f, (FLOAT)MyWindow::cHeight * 0.25f });
	pTestUI->partition(0.05f, 0.05f,
		0.05f, 0.05f,
		0.25f, 0.25f,
		0.4f, 0.4f);

	MyUserInterface* pUItemp = new MyUIButton;
	MyUserInterface* pTemp;

	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_plus_disable.png");
	pUItemp->setSprite(L"test_plus");
	MyVector2F UIPos = pTestUI->m_SPRect.pos + MyVector2F(10.0f, 10.0f);
	MyExRect UIPRect = pUItemp->m_TRect;
	UIPRect.pos = UIPos;
	pUItemp->setPosRect(UIPRect);

	pTestUI->addChild(pUItemp);

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

	pTestUI->addChild(pUItemp);*/


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
	MyExRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		49.5f, 49.5f);
	dummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, BoundaryRect);
	dummy.init();
	dummy.m_fAttackSpeed = 5.0f;
	dummy.m_iDamage = 3;

	//hitDummy Set
	pRect = { 1000.0f, BoundaryRect.fWH.y - 100.0f, 100.0f, 100.0f };
	hitDummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, BoundaryRect);
	hitDummy.init();
	hitDummy.m_iMaxHitPoint = 100;
	hitDummy.m_iCurHitPoint = 100;

	//map obj set
	platForms = new MyTilePlatform;

	MyMapObject* platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 2.0f + 50.0f , BoundaryRect.fWH.y - 50.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 2.0f + i * 50.0f , BoundaryRect.fWH.y - 50.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 1.5f + 50.0f , BoundaryRect.fWH.y - 250.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 1.5f + i * 50.0f , BoundaryRect.fWH.y - 250.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 3.0f + 50.0f , BoundaryRect.fWH.y - 150.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 3.0f + i * 50.0f , BoundaryRect.fWH.y - 150.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { MyWindow::cWidth / 4.0f + 50.0f , BoundaryRect.fWH.y - 350.0f, 150.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { MyWindow::cWidth / 4.0f + i * 50.0f , BoundaryRect.fWH.y - 350.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//Cam set
	mainCam.setBoundaryRect(BoundaryRect);
	mainCam.setFollowTarget(&dummy);

	//timer set
	enemySpawnTimer = 0.0f;

	return true;
}

bool MyInGameScene::frame()
{
	if (dummy.m_iCurHitPoint == 0) { bSceneFlag = 1; }
	//위치 이동
	//pTestUI->frame();
	pBar->frame();
	dummy.frame();
	mainCam.frame();
	BGObj.frame();
	hitDummy.frame();
	platForms->frame();

	//동적 객체 위치 리스트 초기화
	MYSPACE.resetAllDynamicList();

	//동적객체 월드에 다시 배치
	for (auto it : enemyList)
	{
		it->frame();
		MYSPACE.addDynamicObject(it);
	}

	//새로운 적 객체 생성
	randomEnemySpawn();

	//플레이어와의 충돌 객체 리스트 받아오기
	staticCList.clear();
	dynamicCList.clear();
	MYSPACE.getStaticCollisionList(&dummy, staticCList);
	MYSPACE.getDynamicCollisionList(&dummy, dynamicCList);

	//플레이어와 충돌 객체의 충돌처리
	for (auto it : staticCList)
	{
		dummy.staticCollisionHandler(it, instRt);
	}

	for (auto it : dynamicCList)
	{
		instRt = MyCollision::getIntersection2F(dummy.getCSRect(), it->getCSRect());
		dummy.dynamicCollisionHandler(it, instRt);
	}

	//플레이어 투사체 생성부
	if (MAININPUT.getKeyState(VK_LBUTTON) && !dummy.m_bInputNullifyFlag)
	{
		dummy.m_fAttackTimer += MAINTIMER.getOneFrameTimeF();
		if (dummy.m_fAttackTimer > 1.0f / dummy.m_fAttackSpeed)
		{
			dummy.m_fAttackTimer -= 1.0f / dummy.m_fAttackSpeed;
			dummy.createEffect(ePresetList[1], playerEffectList, nullptr);
			dummy.playShotSound();
		}
	}

	//적 객체 수명과 투사체 생성 관리부
	for (eit = enemyList.begin(); eit != enemyList.end(); eit++)
	{
		if (!(*eit)->m_bLifeFlag)
		{
			ecit = eit;
			enemyDeleteList.push_back(ecit);
		}

		if (((*eit)->m_iEnemyId == 2) && ((*eit)->m_state == ES_ATTACK))
		{
			(*eit)->createEffect(ePresetList[1], enemyEffectList, &dummy);
			(*eit)->m_state = ES_IDLE;
		}

		if (((*eit)->m_iEnemyId == 3) && ((*eit)->m_state == ES_ATTACK))
		{
			(*eit)->createEffect(ePresetList[1], enemyEffectList, &dummy);
			(*eit)->m_state = ES_IDLE;
		}
	}

	//플레이어 소유 이펙트 및 투사체의 수명관리 및 충돌 판정 처리
	for (it = playerEffectList.begin(); it != playerEffectList.end(); it++)
	{
		(*it)->update();
		if (!(*it)->m_LifeFlag)
		{
			cit = it;
			playerEffectDeleteList.push_back(cit);
		}
		else
		{
			MyExRect temp;
			if ((*it)->m_fSpeed > 0.0f)
			{
				if (MyCollision::rectToRect((*it)->m_CSRect, hitDummy.getCSRect(), &temp))
				{
					cit = it;
					playerEffectDeleteList.push_back(cit);

					MyEffect* newE = new MyEffect;
					*newE = *ePresetList[0];
					newE->m_SPRect.pos = temp.getCpos();
					newE->m_color = { MYRND.getF(), 0.0f, 0.0f, 1.0f };

					playerEffectList.push_back(newE);

					hitDummy.dynamicCollisionHandler(*it, temp);
					continue;
				}

				for (eit = enemyList.begin(); eit != enemyList.end(); eit++)
				{
					if (MyCollision::rectToRect((*it)->m_CSRect, (*eit)->getCSRect(), &temp))
					{
						cit = it;
						playerEffectDeleteList.push_back(cit);

						MyEffect* newE = new MyEffect;
						*newE = *ePresetList[0];
						newE->m_SPRect.pos = temp.getCpos();
						newE->m_color = { MYRND.getF(), 0.0f, 0.0f, 1.0f };

						playerEffectList.push_back(newE);

						(*eit)->dynamicCollisionHandler(*it, temp);
						break;
					}
				}
			}
		}
	}

	//적 소유 이펙트 및 투사체의 수명관리 및 충돌 판정 처리
	for (it = enemyEffectList.begin(); it != enemyEffectList.end(); it++)
	{
		(*it)->update();
		if (!(*it)->m_LifeFlag)
		{
			cit = it;
			enemyEffectDeleteList.push_back(cit);
		}
		else
		{
			MyExRect temp;
			if ((*it)->m_fSpeed > 0.0f)
			{
				if (MyCollision::rectToRect((*it)->m_CSRect, hitDummy.getCSRect(), &temp))
				{
					cit = it;
					enemyEffectDeleteList.push_back(cit);

					MyEffect* newE = new MyEffect;
					*newE = *ePresetList[0];
					newE->m_SPRect.pos = temp.getCpos();
					newE->m_color = { MYRND.getF(), 0.0f, 0.0f, 1.0f };

					enemyEffectList.push_back(newE);

					hitDummy.dynamicCollisionHandler(*it, temp);
					continue;
				}

				if (MyCollision::rectToRect((*it)->m_CSRect, dummy.getCSRect(), &temp))
				{
					cit = it;
					enemyEffectDeleteList.push_back(cit);

					MyEffect* newE = new MyEffect;
					*newE = *ePresetList[0];
					newE->m_SPRect.pos = temp.getCpos();
					newE->m_color = { 0.0f, MYRND.getF(), 0.0f, 1.0f };

					enemyEffectList.push_back(newE);

					dummy.dynamicCollisionHandler(*it, temp);
					break;
				}
			}
		}
	}

	//삭제될 리소스 처리
	for (const auto it : playerEffectDeleteList)
	{
		MyEffect* temp = *it;
		playerEffectList.erase(it);	//이 과정에서 cit가 가리키고 있는 내용이 사라진다.
		temp->release();
		delete temp;
		temp = nullptr;
	}
	playerEffectDeleteList.clear();

	for (const auto it : enemyEffectDeleteList)
	{
		MyEffect* temp = *it;
		enemyEffectList.erase(it);	//이 과정에서 cit가 가리키고 있는 내용이 사라진다.
		temp->release();
		delete temp;
		temp = nullptr;
	}
	enemyEffectDeleteList.clear();

	for (const auto it : enemyDeleteList)
	{
		MyEnemy* temp = *it;
		enemyList.erase(it);	//이 과정에서 cit가 가리키고 있는 내용이 사라진다.
		temp->release();
		delete temp;
		temp = nullptr;
	}
	enemyDeleteList.clear();

	//후프레임 처리
	postFrame();

	return true;
}

bool MyInGameScene::postFrame()
{
	BGObj.postFrame(mainCam.getCamRect());
	platForms->postFrame(mainCam.getCamRect());

	//pTestUI->postFrame();
	pBar->postFrame();
	dummy.postFrame(mainCam.getCamRect());
	hitDummy.postFrame(mainCam.getCamRect());

	for (std::list<MyEnemy*>::iterator::value_type it : enemyList)
	{
		it->postFrame(mainCam.getCamRect());
	}

	return true;
}

bool MyInGameScene::render()
{
	BGObj.render();
	platForms->render();
	hitDummy.render();

	for (std::list<MyEnemy*>::iterator::value_type it : enemyList)
	{
		it->render();
	}

	for (std::list<MyEffect*>::iterator::value_type it : enemyEffectList)
	{
		it->preRender(mainCam.getCamRect());
		MyEffect::g_pDrawObj->render();
	}

	for (std::list<MyEffect*>::iterator::value_type it : playerEffectList)
	{
		it->preRender(mainCam.getCamRect());
		MyEffect::g_pDrawObj->render();
	}

	dummy.render();

	//pTestUI->render();
	pBar->render();

	wstring mpt = std::to_wstring(MAININPUT.getMousePt().x) + L" " + std::to_wstring(MAININPUT.getMousePt().y);
	TEXT_WRITER.drawT(mpt, (FLOAT)MAININPUT.getMousePt().x, (FLOAT)MAININPUT.getMousePt().y + 50.0f, { 1.0f, 0.0f, 0.0f, 1.0f });

	return true;
}

bool MyInGameScene::release()
{
	dummy.release();
	BGObj.release();
	mainCam.release();
	hitDummy.release();

	for (std::list<MyEffect*>::iterator::value_type it : enemyEffectList)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	enemyEffectList.clear();

	for (std::list<MyEffect*>::iterator::value_type it : playerEffectList)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	playerEffectList.clear();

	for (std::list<MyEffect*>::iterator::value_type it : ePresetList)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	ePresetList.clear();

	for (std::list<MyEnemy*>::iterator::value_type it : enemyList)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	enemyList.clear();

	if (platForms) { platForms->release(); delete platForms; platForms = nullptr;}
	if (pBar) { pBar->release(); delete pBar; pBar = nullptr; }
	//if (pTestUI) { pTestUI->release(); delete pTestUI; pTestUI = nullptr; }

	rPaths.clear();
	staticCList.clear();
	dynamicCList.clear();

	MYSPACE.clear();

	return true;
}

void MyInGameScene::randomEnemySpawn()
{
	enemySpawnTimer += MAINTIMER.getOneFrameTimeF();

	if ((enemySpawnTimer >= 5.0f) && (enemyList.size() <= MAX_ENEMY_NUMBER))
	{
		MYRND_IRANGE(1, 3);

		UINT rnd = MYRND.getI();
		MyExRect pRect = { MYRND.getF(100.0f, BoundaryRect.fWH.x), MYRND.getF(100.0f, BoundaryRect.fWH.y), 75.0f, 75.0f };

		MyEnemy* newE = nullptr;

		if (rnd == 1)
		{
			newE = new E_Seeker;
			newE->setTarget(&dummy);
		}
		else if (rnd == 2)
		{
			newE = new E_Shooter;
			newE->setTarget(&dummy);
		}
		else if (rnd == 3)
		{
			newE = new E_bounder;
			newE->setTarget(&dummy);
		}
		else
		{
			newE = new MyEnemy;
		}
		
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
			pRect, BoundaryRect);
		newE->adjustCRect(pRect);
		newE->init();

		enemyList.push_back(newE);
		enemySpawnTimer = 0.0f;

		MYSPACE.addDynamicObject(newE);
	}
}
