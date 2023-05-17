#include "mygamecore.h"

bool MyGameCore::coreInit()
{
	if (!MyDXDevice::getInstance().create()) { return false; };
	MyDXDevice::getInstance().init();

	if (!MyRenderManager::getInstance().create()) { return false; };
	MyRenderManager::getInstance().init();

	if (!MyWriter::getInstance().create()) { return false; }
	MyWriter::getInstance().init();

	I_TIMER.init();
	I_INPUT.init();

	ob1.create(L"../../hlsl/mydefaultshader.txt", L"../../data/003.jpg");
	ob1.setRect(MyVector2F(300, 300), MyVector2F(100, 100));
	ob2.create(L"../../hlsl/mydefaultshader.txt", L"../../data/004.jpg");
	ob2.setRect(MyVector2F(100, 100), MyVector2F(100, 100));
	
	return true;
}

bool MyGameCore::coreFrame()
{
	I_TIMER.frame();
	I_INPUT.frame();

	ob1.frame();
	ob2.frame();
	return true;
}

bool MyGameCore::coreRender()
{
	PRE_RENDER();

	I_TIMER.render();
	I_INPUT.render();

	//TO DO
	ob1.render();
	ob2.render();

	render();

	POST_RENDER();
	return true;
}

bool MyGameCore::coreRelease()
{
	ob1.release();
	ob2.release();

	I_INPUT.release();
	I_TIMER.release();

	MyTextureManager::getInstance().release();
	MyShaderManager::getInstance().release();
	MyWriter::getInstance().release();
	MyRenderManager::getInstance().release();
	MyDXDevice::getInstance().release();
	return true;
}

bool MyGameCore::render()
{
	wstring time = L"GTime " + to_wstring(I_TIMER.getGametime()) + L"\n";
	time += L"1FrameT " + to_wstring(I_TIMER.getOneFrameTime()) + L"\n";
	time += L"Fps " + to_wstring(I_TIMER.getFps());

	DRAW_TEXT(time.c_str(), 0.0f, 0.0f);
	return true;
}

BOOL MyGameCore::run()
{
	if (!coreInit()) { coreRelease(); return FALSE; }

	bool runFlag = true;

	while (runFlag)
	{
		if (!MyWindow::run()) { runFlag = false; }
		else
		{
			if (!coreFrame() || !coreRender()) 
			{ 
				runFlag = false; 
			}
		}
	}

	coreRelease();

	return true;
}
