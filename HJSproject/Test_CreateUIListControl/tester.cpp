#include "tester.h"

bool TestCase::loadResource()
{
	//map tex
	LOAD_TEXTURE(L"../../data/texture/010.jpg");

	//sprite tex 
	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");

	LOAD_MT_SPRITE(L"../../data/ui/test_UI_list.txt");

	//shader
	LOAD_SHADER(L"../../data/shader/mydefaultshader.txt");
	LOAD_SHADER(L"../../data/shader/mydefaultmaskshader.txt");
	LOAD_SHADER(L"../../data/shader/mydefaultcollisionshader.txt");
	LOAD_SHADER(L"../../data/shader/myalphatextureshader.txt");

	//UI
	LOAD_TEXTURE(L"../../data/ui/UI_empty_list.png");
	LOAD_TEXTURE(L"../../data/ui/UI_plus0.png");

	return true;
}

bool TestCase::init()
{
	loadResource();

	pTestUIButtonList = new MyUIListControl;
	pTestUIButtonList->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_empty_list.png");
	MyRect UIPRect = { 50.0f, 50.0f, 100.0f * 4 + 20.0f * 4, 120.0f };
	pTestUIButtonList->setPosRect(UIPRect);

	for (int i = 0; i < 3; i++)
	{
		temp = new MyUIButton;
		temp->create(L"../../data/shader/mydefaultshader.txt",
			L"../../data/ui/UI_plus0.png");
		temp->setMTsprite(L"test_plus");
		UIPRect = { 60.0f + 120.0f * i, 10.0f + 50.0f, 100.0f, 100.0f };
		temp->setPosRect(UIPRect);

		MyVector4F color;
		color.v[i] = 1.0f;
		color.v[3] = 1.0f;
		temp->setColors(color);

		dynamic_cast<MyUIListControl*>(pTestUIButtonList)->m_ButtonList.push_back(temp);
	}

	temp = new MyUIButton;
	temp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_plus0.png");
	temp->setMTsprite(L"test_plus");
	UIPRect = { 60.0f + 120.0f * 3, 10.0f + 50.0f, 100.0f, 100.0f };
	temp->setPosRect(UIPRect);

	MyVector4F color = {1.0f, 1.0f, 1.0f, 1.0f};
	temp->setColors(color);

	dynamic_cast<MyUIListControl*>(pTestUIButtonList)->m_ButtonList.push_back(temp);

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Height;

	space.maxDepth = 5;
	space.create({ 0.0f, 0.0f }, { bW, bH });

	BoundaryRect = space.getBoundary();

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	//effect preset part
	preset1.createEffectPreset(L"../../data/shader/mydefaultshader.txt",
		L"../../data/sprite_set/test_sprites/sparkle.png", L"sparkle");
	preset1.m_pDrawing->setBoundRect(BoundaryRect);

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

	pTestUIButtonList->frame();
	MyUIListControl* plistCtl = dynamic_cast<MyUIListControl*>(pTestUIButtonList);
	UINT cnt = 0;
	for (vector<MyUserInterface*>::iterator::value_type it : plistCtl->m_ButtonList)
	{
		if (it->m_bState == UB_SELECT)
		{
			FLOAT fRand = MYRND.getF(0.0f, 250.0f);

			MyEffect* newE = new MyEffect;
			newE->m_pEPreset = &preset1;
			newE->init();
			newE->setTimeProperty(10.0f, MYRND.getF(2.0f, 5.0f));
			newE->m_SPRect.pos = { MYRND.getF(0.0f, BoundaryRect.fWH.x), MYRND.getF(0.0f, BoundaryRect.fWH.y) };
			newE->m_SPRect.fWH = { 50.0f + fRand, 50.0f + fRand };
			if (cnt < 3)
			{
				MyVector4F color;
				color.v[cnt] = 1.0f;
				color.v[3] = 1.0f;
				newE->m_color = color;
			}
			else
			{
				MYRND_FRANGE(0.0f, 1.0f);
				MyVector4F color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };
				newE->m_color = color;
			}

			effectList.push_back(newE);
		}
		
		cnt++;
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

	pTestUIButtonList->render();
	
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

	if (pTestUIButtonList) 
	{ 
		pTestUIButtonList->release(); 
		delete pTestUIButtonList;
		pTestUIButtonList = nullptr; 
	}

	return true;
}

GAME_RUN(Test_CreateUIListControl, 800, 800)