#include "tester.h"

bool TestCase::init()
{
	LOAD_TEXTURE(L"../../data/background/3.jpg");

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/background/3.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/background/3.jpg")->m_TextureDesc.Height;

	BoundaryRect.pos = { 0.0f, 0.0f };
	BoundaryRect.fWH = { bW, bH };

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

	subCam.setCamRect({ bW / 2.0f, bH / 2.0f, bW, bH });

	//Dummy Set
	MyRect pRect(MyWindow::cWidth / 2.0f, MyWindow::cHeight / 2.0f,
		99.0f, 99.0f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(L"myalphatextureshader.txt", L"../../data/shapes/Square.png",
		L"../../data/shapes/Square.png", pRect, tRect, BoundaryRect);
	dummy.init();

	//BG Set
	BGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/3.jpg",
		L"../../data/background/3.jpg", pRect, tRect, BoundaryRect);
	BGObj.setBGdefault();

	//sup Set
	pRect = { {(FLOAT)MyWindow::cWidth / 2 - 50.0f, (FLOAT)MyWindow::cHeight * 3 / 4 - 50.0f}, {10.0f, 10.0f} };
	tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
	sup.create(L"myalphatextureshader.txt", L"../../data/shapes/Square.png",
		L"../../data/shapes/Square.png", pRect, tRect, BoundaryRect);
	sup.init();

	//tile set
	for (int i = 0; i < 8; i++)
	{
		MyMapObject2D* newE = new MyMapObject2D;
		pRect = { {50.0f + 100.0f * i, (FLOAT)MyWindow::cHeight - 150.0f}, {100.0f, 100.0f} };
		tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
		newE->create(L"myalphatextureshader.txt", L"../../data/FreeTileset/Tiles/2.png",
			L"../../data/FreeTileset/Tiles/2.png", pRect, tRect, BoundaryRect);

		tileObjects.push_back(newE);
	}
	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyMapObject2D;
		pRect = { {100.0f + 200.0f * i , (FLOAT)MyWindow::cHeight - 250.0f -100.0f * i}, {100.0f, 100.0f} };
		tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
		newE->create(L"myalphatextureshader.txt", L"../../data/FreeTileset/Tiles/2.png",
			L"../../data/FreeTileset/Tiles/2.png", pRect, tRect, BoundaryRect);

		tileObjects.push_back(newE);
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

	MyRect temp = dummy.getPosRect();

	temp.pos += dummy.getDirection() * 100.0f;
	temp = { temp.pos, sup.getPosRect().fWH };

	sup.setPosRect(temp, mainCam.getCamRect());
	sup.frame();
	sup.postFrame(mainCam.getCamRect());

	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) 
	{ 
		it->frame(); 
		it->postFrame(mainCam.getCamRect());
	}

	COLLISION_PLANE cp = MYCP_NONE;
	bool cFlag = false;

	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects)
	{
		if(MyCollision::rectToRect(dummy.getPosRect(), it->getPosRect()))
		{
			cFlag = true;
			COLLISION_PLANE cp = MyCollision::getCollisionPlane(it->getPosRect(),
				dummy.getPosRect(), dummy.getDirection());
			dummy.collisionHandler(cp, it);
		}
	}

	cFlag |= dummy.boundaryCheck();
	if (!cFlag) { dummy.setAerial(); }

	dummy.postFrame(mainCam.getCamRect());

	return true;
}

bool TestCase::render()
{
	BGObj.render();
	dummy.render();
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) { it->render(); }
	sup.render();

	MyRect temp = dummy.getPosRect();
	wstring text = std::to_wstring(temp.pos.x) + L", " + std::to_wstring(temp.pos.y);
	TEXT_WRITER.drawT(text, MyWindow::cWidth * 0.5f - 100.0f, MyWindow::cHeight * 0.5f - 100.0f);


	D3D11_VIEWPORT vs;
	vs.TopLeftX = 0.0f;
	vs.TopLeftY = 0.0f;
	vs.Width = MyWindow::cWidth / 10.0f;
	vs.Height = MyWindow::cHeight / 10.0f;
	vs.MinDepth = 0.0f;
	vs.MaxDepth = 1.0f;

	BGObj.postFrame(subCam.getCamRect());
	dummy.postFrame(subCam.getCamRect());
	sup.postFrame(subCam.getCamRect());
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) { it->postFrame(subCam.getCamRect());; }

	I_DCONTEXT->RSSetViewports(1, &vs);
	BGObj.render();
	dummy.render();
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) { it->render(); }
	sup.render();

	return true;
}

bool TestCase::release()
{
	dummy.release();
	sup.release();
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) 
	{ 
		it->release(); 
		delete it;
		it = nullptr;
	}
	tileObjects.clear();
	BGObj.release();

	//unused
	//mainCam.release();

	return true;
}

GAME_RUN(Test_CameraWithMinimap, 800, 800)