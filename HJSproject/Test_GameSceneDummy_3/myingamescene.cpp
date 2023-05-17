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
	w1bar.create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_full.png");
	w1bar.setPosRect({ { 100.0f, 400.0f },  {140.0f, 18.0f} });
	w1bar.setColors({ 1.0f, 0.0f, 0.0f, 0.6f });
	w1bar.m_barFrame.setColors({ 0.3f, 0.0f, 0.0f, 0.8f });
	w1bar.init();
	w2bar.create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_full.png");
	w2bar.setPosRect({ { 100.0f, 420.0f },  {140.0f, 18.0f} });
	w2bar.setColors({ 0.0f, 0.0f, 1.0f, 0.6f });
	w2bar.m_barFrame.setColors({ 0.0f, 0.0f, 0.3f, 0.8f });
	w2bar.init(); 
	w3bar.create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_charge_bar_full.png");
	w3bar.setPosRect({ { 100.0f, 440.0f },  {140.0f, 18.0f} });
	w3bar.setColors({ 0.0f, 1.0f, 0.0f, 0.6f });
	w3bar.m_barFrame.setColors({ 0.0f, 0.3f, 0.0f, 0.8f });
	w3bar.init();

	pReinforceUI = new MyShopDialog;
	pReinforceUI->create(rPaths[0] + L"mydefaultshader.txt", rPaths[4] + L"UI_paperframe.png");
	pReinforceUI->setPosRect({ 100.0f, 100.0f, 75.0f, 75.0f });
	pReinforceUI->partition(0.2f, 0.2f,
		0.2f, 0.2f,
		0.2f, 0.2f,
		0.2f, 0.2f);

	MyUserInterface* pUItemp = new MyUIButton;
	MyUserInterface* pTemp;
	MyExRect UIPRect;

	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/Pixel_Art_Buttons.png");
	pUItemp->setSprite(L"test_expand");
	MyVector2F UIPos = pReinforceUI->m_SPRect.pos + MyVector2F(12.5f, 14.0f);
	MyVector2F UIWH = { 50.0f, 50.0f };
	pUItemp->setPosRect(MyExRect(UIPos, UIWH));

	pReinforceUI->addChild(pUItemp);

	pUItemp = new MyUIListControl;
	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_empty_list.png");
	UIPRect.pos = pReinforceUI->m_SPRect.pos + MyVector2F(95.0f, -25.0f);
	UIPRect.fWH = { 100.0f * 3 + 20.0f * 3, 120.0f };
	pUItemp->setPosRect(UIPRect);

	for (int i = 0; i < 3; i++)
	{
		pTemp = new MyUIButton;
		pTemp->create(L"../../data/shader/mydefaultshader.txt",
			L"../../data/ui/Pixel_Art_Buttons.png");
		UIPRect = { pUItemp->m_SPRect.pos.x + 10.0f + 120.0f * i, pUItemp->m_SPRect.pos.y + 15.0f, 100.0f, 100.0f };
		pTemp->setPosRect(UIPRect);
		pTemp->m_bAvailableFlag = false;

		pUItemp->addChild(pTemp);
	}

	pUItemp->m_pChild[0]->setSprite(L"test_attack_up");
	pUItemp->m_pChild[1]->setSprite(L"test_attackspeed_up");
	pUItemp->m_pChild[2]->setSprite(L"test_health_regen");

	pReinforceUI->addChild(pUItemp);

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
	newPreset->m_fSpeed = 350.0f;
	newPreset->m_iDamage = 0;
	newPreset->setTimeProperty(3.0f, 3.0f);
	ePresetList.push_back(newPreset);

	//bullet : 2
	newPreset = new MyProjectile;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_SPRect.fWH = { 20.0f, 20.0f };
	newPreset->m_fSpeed = 500.0f;
	newPreset->m_iDamage = 2;
	newPreset->m_BRect = BoundaryRect;
	newPreset->setTimeProperty(0.5f, 0.5f);
	ePresetList.push_back(newPreset);

	//bullet : 3
	newPreset = new MyProjectile;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_SPRect.fWH = { 30.0f, 30.0f };
	newPreset->m_fSpeed = 1000.0f;
	newPreset->m_iDamage = 5;
	newPreset->m_BRect = BoundaryRect;
	newPreset->setTimeProperty(3.0f, 3.0f);
	ePresetList.push_back(newPreset);

	//create : 4
	newPreset = new MyEffect;
	newPreset->create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"circle.png", L"circle");
	newPreset->m_BRect = BoundaryRect;
	newPreset->m_SPRect.fWH = { 30.0f, 30.0f };
	newPreset->setTimeProperty(1.0f, 1.0f);
	newPreset->m_color = { 0.0f, 1.0f, 0.0f, 0.2f };
	ePresetList.push_back(newPreset);
	ePresetList[1]->m_pCreateEPresets.push_back(ePresetList[2]);

	//destruct : 5
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

	gamePlatformSet();

	//Cam set
	mainCam.setBoundaryRect(BoundaryRect);
	mainCam.setFollowTarget(&dummy);

	//timer set
	enemySpawnTimer = 0.0f;
	enemyHealthMultiflier = 1.0f;

	return true;
}

bool MyInGameScene::frame()
{
	if (dummy.m_iCurHitPoint < 0) { bSceneFlag = 1; }

	//위치 이동
	pReinforceUI->frame();

	if (pReinforceUI->m_pChild[0]->m_bState == UB_SELECT)
	{
		pReinforceUI->m_bAvailableFlag = !pReinforceUI->m_bAvailableFlag;
	}

	if (w1bar.m_bMaxFlag && pReinforceUI->m_pChild[1]->m_pChild[0]->m_bState == UB_SELECT)
	{
		dummy.m_iAttackGrade++;
		w1bar.m_fCurStack = 0.0f;
		w1bar.gradeUp();
		w1bar.m_bMaxFlag = false;
		pReinforceUI->m_pChild[1]->m_pChild[0]->m_bAvailableFlag = false;
	}
	if (w2bar.m_bMaxFlag && pReinforceUI->m_pChild[1]->m_pChild[1]->m_bState == UB_SELECT)
	{
		dummy.m_iArrackSpeedGrade++;
		w2bar.m_fCurStack = 0.0f;
		w2bar.gradeUp();
		w2bar.m_bMaxFlag = false;
		pReinforceUI->m_pChild[1]->m_pChild[1]->m_bAvailableFlag = false;
	}
	if (w3bar.m_bMaxFlag && pReinforceUI->m_pChild[1]->m_pChild[2]->m_bState == UB_SELECT)
	{
		dummy.m_iHpGen++;
		w3bar.m_fCurStack = 0.0f;
		w3bar.gradeUp();
		w3bar.m_bMaxFlag = false;
		pReinforceUI->m_pChild[1]->m_pChild[2]->m_bAvailableFlag = false;
	}

	w1bar.frame();
	dummy.frame();
	mainCam.frame();
	BGObj.frame();
	hitDummy.frame();
	platForms->frame();

	//정적 충돌 처리
	staticCList.clear();
	MYSPACE.getStaticCollisionList(&dummy, staticCList);
	for (auto it : staticCList)
	{
		dummy.staticCollisionHandler(it, instRt);
	}

	//새로운 적 객체 생성
	randomEnemySpawn();

	//동적 객체 위치 리스트 초기화
	MYSPACE.resetAllDynamicList();

	//동적객체 월드에 다시 배치
	for (auto it : enemyList)
	{
		it->frame();
		MYSPACE.addDynamicObject(it);
	}

	//플레이어와의 충돌 객체 리스트 받아오기
	dynamicCList.clear();
	MYSPACE.getDynamicCollisionList(&dummy, dynamicCList);

	//플레이어와 충돌 객체의 충돌처리
	for (auto it : dynamicCList)
	{
		instRt = MyCollision::getIntersection2F(dummy.getCSRect(), it->getCSRect());
		dummy.dynamicCollisionHandler(it, instRt);
		it->dynamicCollisionHandler(&dummy, instRt);

	}

	if (MAININPUT.getKeyState('1') == KEY_DOWN) { dummy.m_weaponType = 1; dummy.m_fAttackTimer = 0.0f; }
	if (MAININPUT.getKeyState('2') == KEY_DOWN) { dummy.m_weaponType = 2; dummy.m_fAttackTimer = 0.0f; }
	if (MAININPUT.getKeyState('3') == KEY_DOWN) { dummy.m_weaponType = 3; dummy.m_fAttackTimer = 0.0f; }

	dummy.m_fAttackTimer += MAINTIMER.getOneFrameTimeF();

	switch (dummy.m_weaponType)
	{
	case 2:
		if (dummy.m_fAttackTimer > ((10.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade)) * 3))
		{
			dummy.m_fAttackTimer = (10.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade)) * 3;
		}
		break;
	case 3:
		if (dummy.m_fAttackTimer > ((3.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 2.5f)) * 3))
		{
			dummy.m_fAttackTimer = (3.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 2.5f)) * 3;
		}
		break;
	default:
		if (dummy.m_fAttackTimer > ((1.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 4.0f)) * 3))
		{
			dummy.m_fAttackTimer = (1.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 4.0f)) * 3;
		}
		break;
	}

	//플레이어 투사체 생성부
	if (MAININPUT.getKeyState(VK_LBUTTON) && !dummy.m_bInputNullifyFlag)
	{
		switch (dummy.m_weaponType)
		{
		case 2:
			if (dummy.m_fAttackTimer > 10.0f / dummy.m_fAttackSpeed)
			{
				dummy.m_fAttackTimer -= 10.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 1.5f);
				dummy.createEffect(ePresetList[2], playerEffectList, nullptr);
				dummy.playShotSound();
			}
			break;
		case 3:
			if (dummy.m_fAttackTimer > 3.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 2.5f))
			{
				dummy.m_fAttackTimer -= 3.0f / dummy.m_fAttackSpeed;
				dummy.createEffect(ePresetList[3], playerEffectList, nullptr);
				dummy.playShotSound();
			}
			break;
		default:
			if (dummy.m_fAttackTimer > 1.0f / (dummy.m_fAttackSpeed + dummy.m_iArrackSpeedGrade * 4.0f))
			{
				dummy.m_fAttackTimer -= 1.0f / dummy.m_fAttackSpeed;
				dummy.createEffect(ePresetList[1], playerEffectList, nullptr);
				dummy.playShotSound();
			}
			break;
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
						
						switch ((*it)->m_eIdx)
						{
							case 1: w1bar.m_fCurStack += 1.0f; break;
							case 2: w2bar.m_fCurStack += 5.0f; break;
							case 3: w3bar.m_fCurStack += 2.5f; break;
						}

						break;
					}
				}
			}
		}
	}

	if (w1bar.m_bMaxFlag) { pReinforceUI->m_pChild[1]->m_pChild[0]->m_bAvailableFlag = TRUE; }
	if (w2bar.m_bMaxFlag) { pReinforceUI->m_pChild[1]->m_pChild[1]->m_bAvailableFlag = TRUE; }
	if (w3bar.m_bMaxFlag) { pReinforceUI->m_pChild[1]->m_pChild[2]->m_bAvailableFlag = TRUE; }

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
	w1bar.postFrame();
	w2bar.postFrame();
	w3bar.postFrame();
	BGObj.postFrame(mainCam.getCamRect());
	platForms->postFrame(mainCam.getCamRect());

	pReinforceUI->postFrame();
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

	pReinforceUI->render();
	w1bar.render();
	w2bar.render();
	w3bar.render();

	wstring mpt = std::to_wstring(MAININPUT.getMousePt().x) + L" " + std::to_wstring(MAININPUT.getMousePt().y);
	TEXT_WRITER.drawT(mpt, (FLOAT)MAININPUT.getMousePt().x, (FLOAT)MAININPUT.getMousePt().y + 50.0f, { 1.0f, 0.0f, 0.0f, 1.0f });

	return true;
}

bool MyInGameScene::release()
{
	w1bar.release();
	w2bar.release();
	w3bar.release();

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
	if (pReinforceUI) { pReinforceUI->release(); delete pReinforceUI; pReinforceUI = nullptr; }

	rPaths.clear();
	staticCList.clear();
	dynamicCList.clear();

	MYSPACE.clear();

	bSceneFlag = 0;

	return true;
}

void MyInGameScene::randomEnemySpawn()
{
	enemySpawnTimer += MAINTIMER.getOneFrameTimeF();

	if ((enemySpawnTimer >= 8.0f) && (enemyList.size() <= MAX_ENEMY_NUMBER))
	{
		enemyHealthMultiflier += 0.1f;
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
		newE->m_iMaxHitPoint += (FLOAT)newE->m_iMaxHitPoint * enemyHealthMultiflier;
		newE->m_iCurHitPoint = newE->m_iMaxHitPoint;
		newE->init();

		enemyList.push_back(newE);
		enemySpawnTimer = 0.0f;

		MYSPACE.addDynamicObject(newE);
	}
}

void MyInGameScene::gamePlatformSet()
{
	//map obj set
	platForms = new MyTilePlatform;

	MyExRect pRect;

	//vertical wall
	//0 ~ 300
	MyMapObject* platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { BoundaryRect.fWH.x / 2.0f , 150.0f, 100.0f, 300.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { BoundaryRect.fWH.x / 2.0f , 50.0f + i * 100.0f, 100.0f, 100.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//600 ~ 1000
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { BoundaryRect.fWH.x / 2.0f , 800.0f, 100.0f, 400.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { BoundaryRect.fWH.x / 2.0f , 650.0f + i * 100.0f, 100.0f, 100.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//1300 ~ 1600
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { BoundaryRect.fWH.x / 2.0f , 1450.0f, 100.0f, 300.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 3; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { BoundaryRect.fWH.x / 2.0f , 1350.0f + i * 100.0f, 100.0f, 100.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//Horizontal Platform
	//중앙 최하단 200너비 플랫폼 왼쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1050.0f , 1325.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 975.0f + i * 50.0f , 1325.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 최하단 200너비 플랫폼 오른쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1350.0f , 1325.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 1275.0f + i * 50.0f , 1325.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 하단 400너비 플랫폼 왼쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 950.0f , 975.0f, 400.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 8; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 775.0f + i * 50.0f , 975.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 하단 400너비 플랫폼 오른쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1450.0f , 975.0f, 400.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 8; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 1275.0f + i * 50.0f , 975.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 상단 400너비 플랫폼 왼쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 950.0f , 625.0f, 400.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 8; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 775.0f + i * 50.0f , 625.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 상단 400너비 플랫폼 오른쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1450.0f , 625.0f, 400.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 8; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 1275.0f + i * 50.0f , 625.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 최상단 200너비 플랫폼 왼쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1050.0f , 275.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 975.0f + i * 50.0f , 275.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//중앙 최상단 200너비 플랫폼 오른쪽
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 1350.0f , 275.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 1275.0f + i * 50.0f , 275.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//왼쪽 중앙 상단 200너비 플랫폼
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 300.0f , 200.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 225.0f + i * 50.0f , 200.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//왼쪽 중앙 하단 200너비 플랫폼
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 300.0f , 1400.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 225.0f + i * 50.0f , 1400.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//오른쪽 중앙 상단 200너비 플랫폼
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 2100.0f, 200.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 2025.0f + i * 50.0f , 200.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);

	//오른쪽 중앙 하단 200너비 플랫폼
	platForm = new MyTilePlatform;
	platForm->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
	pRect = { 2100.0f , 1400.0f, 200.0f, 50.0f };
	platForm->setPosRect(pRect);
	platForm->adjustCRect(pRect);

	for (int i = 0; i < 4; i++)
	{
		MyMapObject* newE = new MyTile;
		pRect = { 2025.0f + i * 50.0f , 1400.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect);

		platForm->addChild(newE);
	}
	platForms->addChild(platForm);
	MYSPACE.addStaticObject(platForm);
}
