#include "tester.h"

bool TestCase::init()
{
	mapObj.create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/arkanoid/nes_arkanoid_fields.png",
		0, 0, 192, 232);
	mapObj.init();


	playerObj.create(L"../../data/shader/mydefaultmaskshader.txt",
		L"../../data/arkanoid/nes_arkanoid_vaus.png",
		L"../../data/arkanoid/nes_arkanoid_vaus_mask.png",
		{ {(FLOAT)MyWindow::cWidth / 2 - 16*3, (FLOAT)MyWindow::cHeight * 13 / 15, 0.0f}, {32*3, 8*3, 0.0f} },
		{ {0.0f, 0.0f, 0.0f}, {32.0f, 8.0f, 0.0f} });
	playerObj.init();

	for (int i = 0; i < 10; i++)
	{
		MyDynamicObject* newE = new MyDynamicObject;

		DynamicObjectList.push_back(newE);
		DynamicObjectList[i]->create(L"../../data/shader/mydefaultmaskshader.txt",
			L"../../data/arkanoid/nes_arkanoid_vaus.png",
			L"../../data/arkanoid/nes_arkanoid_vaus_mask.png",
			{ {(FLOAT)MyWindow::cWidth / 2 - 2.5f * 3, (FLOAT)MyWindow::cHeight / 2, 0.0f}, {5 * 3, 4 * 3, 0.0f} },
			{ {40.0f, 0.0f, 0.0f}, {5.0f, 4.0f, 0.0f} });
		DynamicObjectList[i]->init();
	}

	return true;
}

bool TestCase::frame()
{
	mapObj.frame();
	playerObj.frame();

	MyCube pRt = playerObj.getPosRect();
	MyCube dRt;
	MyVector3F vD;
	for (int i = 0; i < 10; i++) 
	{ 
		DynamicObjectList[i]->frame(); 
		dRt = DynamicObjectList[i]->getPosRect();

		if (MyCollision::cubeToCube(pRt, dRt))
		{
			vD = DynamicObjectList[i]->getDirection();

			UINT ret = MyCollision::getCollisionPlane(pRt, dRt, vD);

			if (ret == MYCP_TOP || ret == MYCP_BOT) 
			{ 
				if (ret == MYCP_TOP) { dRt.pos.y = pRt.pos.y - dRt.fWLH.v[1] - 5.0f - 1.0f; }
				else { dRt.pos.y = pRt.pos.y + pRt.fWLH.v[1] + 5.0f + 1.0f; }
				vD.y = -vD.y;
				DynamicObjectList[i]->setDirection(vD);
			}
			else 
			{
				if (ret == MYCP_LEFT) { dRt.pos.x = pRt.pos.x - dRt.fWLH.v[0] - 5.0f - 1.0f; }
				else { dRt.pos.x = pRt.pos.x + pRt.fWLH.v[0] + 5.0f + 1.0f; }
				vD.x = -vD.x;
				DynamicObjectList[i]->setDirection(vD);
			}
		}
	}
	
	return true;
}

bool TestCase::render()
{
	mapObj.render();
	playerObj.render();

	for (int i = 0; i < 10; i++) { DynamicObjectList[i]->render(); }
	return true;
}

bool TestCase::release()
{
	mapObj.release();
	playerObj.release();

	for (int i = 0; i < 10; i++)
	{
		DynamicObjectList[i]->release();
		delete DynamicObjectList[i];
		DynamicObjectList[i] = nullptr;
	}

	DynamicObjectList.clear();
	return true;
}

GAME_RUN(Object Collision Detection, 192*3, 232*3)