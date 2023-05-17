#include "tester.h"

bool TestCase::init()
{
	BoundaryRect.pos = { 0.0f, 0.0f };
	BoundaryRect.fWH = { (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight };

	//Dummy Set
	MyRect pRect((FLOAT)MyWindow::cWidth / 2 - 50.0f, (FLOAT)MyWindow::cHeight * 0.5f - 50.0f,
		100.0f, 100.0f);
	MyRect tRect(0.0f, 0.0f, 100.0f, 100.0f);
	dummy.create(L"myalphatextureshader.txt", L"../../data/shapes/Square.png",
		L"../../data/shapes/Square.png", pRect, tRect, BoundaryRect);
	dummy.init();

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
		pRect = { {100.0f * i, (FLOAT)MyWindow::cHeight - 100.0f}, {100.0f, 100.0f} };
		tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
		newE->create(L"myalphatextureshader.txt", L"../../data/FreeTileset/Tiles/2.png",
			L"../../data/FreeTileset/Tiles/2.png", pRect, tRect, BoundaryRect);

		tileObjects.push_back(newE);
	}
	for (int i = 0; i < 3; i++)
	{
		MyMapObject2D* newE = new MyMapObject2D;
		pRect = { {100.0f + 200.0f * i , (FLOAT)MyWindow::cHeight - 200.0f -100.0f * i}, {100.0f, 100.0f} };
		tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
		newE->create(L"myalphatextureshader.txt", L"../../data/FreeTileset/Tiles/2.png",
			L"../../data/FreeTileset/Tiles/2.png", pRect, tRect, BoundaryRect);

		tileObjects.push_back(newE);
	}

	return true;
}

bool TestCase::frame()
{
	dummy.frame();

	MyRect temp = dummy.getPosRect();

	temp.pos.x += temp.fWH.v[0] * 0.5f - sup.getPosRect().fWH.v[0] * 0.5f;
	temp.pos.y += temp.fWH.v[1] * 0.5f - sup.getPosRect().fWH.v[1] * 0.5f;
	temp.pos += dummy.getDirection() * 100.0f;
	temp = { temp.pos, sup.getPosRect().fWH };

	sup.setPosRect(temp);
	sup.frame();

	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) { it->frame(); }

	COLLISION_PLANE cp = MYCP_NONE;
	bool cFlag = false;

	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects)
	{
		while (MyCollision::rectToRect(dummy.getPosRect(), it->getPosRect()))
		{
			cFlag = true;
			COLLISION_PLANE cp = MyCollision::getCollisionPlane(it->getPosRect(),
				dummy.getPosRect(), dummy.getDirection());
			dummy.collisionHandler(cp, it);
		}
	}

	temp = dummy.getPosRect();

	if (temp.pos.x <= 0.0f) 
	{ 
		cFlag = true;
		dummy.collisionHandler(MYCP_RIGHT);
	}
	if (temp.pos.x >= MyWindow::cWidth - temp.fWH.v[0]) 
	{ 
		cFlag = true;
		dummy.collisionHandler(MYCP_LEFT);
	}
	if (temp.pos.y <= 0.0f) 
	{ 
		cFlag = true;
		dummy.collisionHandler(MYCP_BOT);
	}
	if (temp.pos.y >= (FLOAT)MyWindow::cHeight - temp.fWH.v[1]) 
	{ 
		cFlag = true;
		dummy.collisionHandler(MYCP_TOP);
	}
	if (!cFlag)
	{
		//이걸 빼면 공중에서 한번 점프 가능
		dummy.collisionHandler(MYCP_NONE);
	}

	dummy.postframe();
	return true;
}

bool TestCase::render()
{
	dummy.render();
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) { it->render(); }
	sup.render();

	MyRect temp = dummy.getPosRect();
	wstring text = std::to_wstring(temp.pos.x) + L", " + std::to_wstring(temp.pos.y);
	TEXT_WRITER.drawT(text, temp.pos.x + 50.0f, temp.pos.y - 50.0f);
	return true;
}

bool TestCase::release()
{
	sup.release();
	dummy.release();
	for (vector<MyMapObject2D*>::iterator::value_type it : tileObjects) 
	{ 
		it->release(); 
		delete it;
		it = nullptr;
	}
	tileObjects.clear();

	return true;
}

GAME_RUN(Test_GroundTileWithObject_0, 800, 800)