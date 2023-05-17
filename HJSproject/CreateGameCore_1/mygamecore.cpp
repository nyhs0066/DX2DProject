#include "mygamecore.h"

bool MyGameCore::coreInit()
{
	if (!MyDXDevice::getInstance().create()) { return false; };
	MyDXDevice::getInstance().init();

	if (!MyRenderManager::getInstance().create()) { return false; };
	MyRenderManager::getInstance().init();

	m_timer.init();
	m_writer.create();
	m_writer.init();
	m_input.init();

	return true;
}

bool MyGameCore::coreFrame()
{
	m_timer.frame();
	m_writer.frame();
	m_input.frame();
	return true;
}

bool MyGameCore::coreRender()
{
	PRE_RENDER();

	//TO DO
	m_timer.render();
	m_input.render();
	m_writer.render();
	render();

	POST_RENDER();
	return true;
}

bool MyGameCore::coreRelease()
{
	m_input.release();
	m_writer.release();
	MyRenderManager::getInstance().release();
	MyDXDevice::getInstance().release();
	return true;
}

bool MyGameCore::render()
{
	wstring time = to_wstring(m_timer.getGametime()) + L"   ";
	time += to_wstring(m_timer.getOneFrameTime()) + L"   ";
	time += to_wstring(m_timer.fps) + L"\n";

	m_writer.draw(time.c_str(), 50.0f, 400.0f);

	if (m_input.getKState('A') == KS_HOLD)
	{
		m_writer.draw(L"AKEYHOLD", 50.0f, 150.0f);
	}
	if (m_input.getKState('S') == KS_HOLD)
	{
		m_writer.draw(L"SKEYHOLD", 50.0f, 175.0f);
	}
	if (m_input.getKState('W') == KS_HOLD)
	{
		m_writer.draw(L"WKEYHOLD", 50.0f, 200.0f);
	}
	if (m_input.getKState('D') == KS_HOLD)
	{
		m_writer.draw(L"DKEYHOLD", 50.0f, 225.0f);
	}
	if (m_input.getKState('Q') == KS_HOLD)
	{
		m_writer.draw(L"QKEYHOLD", 50.0f, 250.0f);
	}
	if (m_input.getKState('E') == KS_HOLD)
	{
		m_writer.draw(L"EKEYHOLD", 50.0f, 275.0f);
	}
	if (m_input.getKState(VK_LBUTTON) == KS_HOLD)
	{
		wstring pt;
		m_input.mousePt;
		pt = L"X : " + to_wstring(m_input.mousePt.x);
		pt += L"Y : " + to_wstring(m_input.mousePt.y);

		m_writer.draw(pt.c_str(), 50.0f, 300.0f);
	}

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
