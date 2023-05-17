#include "mygamecore.h"

bool MyGameCore::coreInit()
{
	if (!MyDXDevice::getInstance().create()) { return false; };
	MyDXDevice::getInstance().init();

	if (!MyRenderManager::getInstance().create()) { return false; };
	MyRenderManager::getInstance().init();

	m_writer.create();
	m_writer.init();

	return true;
}

bool MyGameCore::coreFrame()
{
	m_writer.frame();
	return true;
}

bool MyGameCore::coreRender()
{
	PRE_RENDER();

	//TO DO
	m_writer.render();

	POST_RENDER();
	return true;
}

bool MyGameCore::coreRelease()
{
	m_writer.release();
	MyRenderManager::getInstance().release();
	MyDXDevice::getInstance().release();
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
