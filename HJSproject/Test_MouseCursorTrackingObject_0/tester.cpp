#include "tester.h"

bool TestCase::init()
{
	LOAD_TEXTURE(L"../../data/shapes/numeric.png");
	LOAD_TEXTURE(L"../../data/sprite_set/test_sprites/sparkle.png");
	LOAD_ST_SPRITE(L"../../data/sprite_set/test_sprites/sprite_rect_list.txt");

	FLOAT bW = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Width;
	FLOAT bH = (FLOAT)LOAD_TEXTURE(L"../../data/texture/010.jpg")->m_TextureDesc.Height;

	BoundaryRect.pos = { 0.0f, 0.0f };
	BoundaryRect.fWH = { bW, bH };

	mainCam.setCamRect({ MyWindow::cWidth / 2.0f, bH - MyWindow::cHeight / 2.0f,
		(FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

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

	//sup Set
	pRect = { {(FLOAT)MyWindow::cWidth / 2 - 50.0f, (FLOAT)MyWindow::cHeight * 3 / 4 - 50.0f}, {10.0f, 10.0f} };
	tRect = { {0.0f, 0.0f}, {100.0f, 100.0f} };
	sup.create(L"../../data/shader/myalphatextureshader.txt", L"../../data/shapes/Square.png",
		pRect, tRect, BoundaryRect);
	sup.init();

	//effect list set
	/*pRect.pos.x = 0.0f;
	for (int i = 0; i < 10; i++)
	{
		pRect.pos.x += 100.0f;
		pRect.fWH = { 100.0f, 100.0f };

		MyEffect* newE = new MyEffect;
		newE->create(L"../../data/shader/myalphatextureshader.txt", L"../../data/sprite_set/test_sprites/sparkle.png",
			pRect, tRect, BoundaryRect);
		newE->loadSprite(L"sparkle");
		newE->m_fLifeSpanT = 10.0f + i;
		newE->m_fplayT = 1.0f;
		newE->m_fStepT = newE->m_fplayT / newE->m_pSprite->m_spriteArray.size();

		effectList.push_back(newE);
	}*/

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

	/*for (std::list<MyEffect*>::iterator it = effectList.begin();
		it != effectList.end();)
	{
		std::list<MyEffect*>::const_iterator cit = it;
		it++;
		if ((*cit)->frame()) { (*cit)->postFrame(mainCam.getCamRect()); }
		else
		{
			delete *cit;
			effectList.erase(cit);
		}
	}*/

	MyRect temp = dummy.getPosRect();
	MyRect temp2 = temp;
	POINT cursorPt = MAININPUT.getMousePt();
	MyVector2F cPos = mainCam.getCamPos();
	MyVector2F cFWH = mainCam.getCamArea();
	MyVector2F vDirection = { cursorPt.x - (temp.pos.x - cPos.x + MyWindow::cWidth*0.5f),
		cursorPt.y - (temp.pos.y - cPos.y + MyWindow::cHeight * 0.5f) };
	vDirection.normalization();

	temp.pos += vDirection * 100.0f;
	temp = { temp.pos, sup.getPosRect().fWH };

	sup.setPosRect(temp, mainCam.getCamRect());
	sup.frame();
	sup.postFrame(mainCam.getCamRect());

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
	sup.render();

	MyVector2F Upos = dummy.getPosRect().pos;
	MyVector2F CPos = mainCam.getCamPos();
	TEXT_WRITER.drawT(std::to_wstring(CPos.x) + L" " + std::to_wstring(CPos.y), 400, 300);
	TEXT_WRITER.drawT(std::to_wstring(Upos.x) + L" " + std::to_wstring(Upos.y), 400, 400);
	/*for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		it->render();
	}*/
	
	return true;
}

bool TestCase::release()
{
	dummy.release();
	sup.release();

	BGObj.release();
	/*for (std::list<MyEffect*>::iterator::value_type it : effectList)
	{
		delete it;
		it = nullptr;
	}
	effectList.clear();*/

	/*unused
	test.release();
	mainCam.release();*/

	return true;
}

GAME_RUN(Test_MouseCursorTrackingObject_0, 800, 800)