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
	LOAD_TEXTURE(L"../../data/ui/UI_popup.title.png");
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

	//UI Set
	testUI.wszShaderName = rPaths[0] + L"mydefaultshader.txt";
	testUI.wszTextureName = rPaths[4] + L"UI_popup_title.png";
	testUI.create(testUI.wszShaderName, testUI.wszTextureName);
	testUI.setPosRect({ (FLOAT)MyWindow::cWidth * 0.75f, (FLOAT)MyWindow::cHeight * 0.0f, (FLOAT)MyWindow::cWidth*0.25f, (FLOAT)MyWindow::cHeight*0.25f });
	testUI.partition(	0.05f, 0.05f,
						0.05f, 0.05f,
						0.25f, 0.25f,
						0.4f, 0.4f);

	MyUserInterface* pUItemp = new MyUIButton;
	MyUserInterface* pTemp;

	pUItemp->create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/ui/UI_plus0.png");
	pUItemp->setMTsprite(L"test_plus");
	MyVector2F UIPos = testUI.getPosRect().pos + MyVector2F(10.0f, 10.0f);
	MyRect UIPRect = pUItemp->getTexRect();
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
			L"../../data/ui/UI_plus0.png");
		pTemp->setMTsprite(L"test_plus");
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
	preset1.create(rPaths[0] + L"mydefaultshader.txt",
		rPaths[3] + L"sparkle.png", L"sparkle");
	preset1.m_pDrawing->setBoundRect(BoundaryRect);

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		49.5f, 49.5f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png",
		pRect, tRect, BoundaryRect);
	dummy.init();

	//map obj Set
	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyTile2D;
		pRect = { MyWindow::cWidth / 2.0f + i * 50.0f , BoundaryRect.fWH.y - 50.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect, mainCam.getCamRect());
		newE->setBoundRect(BoundaryRect);

		test.m_mapObjList.push_back(newE);
		space.addStaticObject(newE);
	}

	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyTile2D;
		pRect = { MyWindow::cWidth / 1.5f + i * 50.0f , BoundaryRect.fWH.y - 250.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect, mainCam.getCamRect());
		newE->setBoundRect(BoundaryRect);

		test.m_mapObjList.push_back(newE);
		space.addStaticObject(newE);
	}

	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyTile2D;
		pRect = { MyWindow::cWidth / 3.0f + i * 50.0f , BoundaryRect.fWH.y - 150.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect, mainCam.getCamRect());
		newE->setBoundRect(BoundaryRect);

		test.m_mapObjList.push_back(newE);
		space.addStaticObject(newE);
	}

	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyTile2D;
		pRect = { MyWindow::cWidth / 4.0f + i * 50.0f , BoundaryRect.fWH.y - 350.0f, 50.0f, 50.0f };
		newE->create(rPaths[0] + L"mydefaultshader.txt", rPaths[2] + L"Square.png");
		newE->setPosRect(pRect, mainCam.getCamRect());
		newE->setBoundRect(BoundaryRect);

		test.m_mapObjList.push_back(newE);
		space.addStaticObject(newE);
	}

	//Cam Set
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

	test.frame();
	test.postFrame(mainCam.getCamRect());

	cList.clear();
	space.getCollisionList(&dummy, cList);
	for (auto it : cList)
	{
		dummy.staticCollisionHandler(it, instRt);
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

	dummy.postFrame(mainCam.getCamRect());

	MyRect move = testUI.getPosRect();
	move.pos.x += MAINTIMER.getOneFrameTimeF() * 10.0f;
	move.pos.y += MAINTIMER.getOneFrameTimeF() * 10.0f;
	testUI.setPosRect(move);
	testUI.frame();

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();
	test.render();
	
	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		it->preRender(mainCam.getCamRect());
		it->m_pEPreset->m_pDrawing->render();
	}

	testUI.render();
	
	return true;
}

bool TestCase::release()
{
	dummy.release();
	BGObj.release();
	test.release();

	for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();

	testUI.release();

	return true;
}

GAME_RUN(Test_CreateUIDialog_0, 800, 800)