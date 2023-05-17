#include "myuserinterface.h"

MyUserInterface::MyUserInterface() 
{
	m_UISTsprite = nullptr;
	m_UIMTsprite = nullptr;

	m_bState = UB_DISABLE;
}

MyUserInterface::~MyUserInterface() {}

bool MyUserInterface::setSTsprite(wstring wszSpriteName)
{
	if (m_UISTsprite = GET_ST_SPRITE(wszSpriteName)) { return true; }

	return false;
}

bool MyUserInterface::setMTsprite(wstring wszSpriteName)
{
	if (m_UIMTsprite = GET_MT_SPRITE(wszSpriteName)) { return true; }

	return false;
}

bool MyUserInterface::frame()
{
	setPosRect(m_SPRect);
	return true;
}

MyUIButton::MyUIButton() {}

MyUIButton::~MyUIButton() {}

bool MyUIButton::frame()
{
	POINT pt = MAININPUT.getMousePt();
	MyVector2F fPt = { (FLOAT)pt.x, (FLOAT)pt.y };

	if (MyCollision::pointToRect(fPt, m_SPRect))
	{
		UINT input = MAININPUT.getKeyState(VK_LBUTTON);
		if (input)
		{
			m_bState = UB_PUSH;
			if (input == KEY_UP) { m_bState = UB_SELECT; }
		}
		else { m_bState = UB_HOVER; }
	}
	else { m_bState = UB_IDLE; }

	if (m_UISTsprite) { setTexRect(m_UISTsprite->m_spriteArray[m_bState]); }	
	else 
	{ 
		if (m_bState == UB_SELECT) { setTexture(m_UIMTsprite->m_spriteArray[UB_PUSH]); }
		else { setTexture(m_UIMTsprite->m_spriteArray[m_bState]); }
	}

	setPosRect(m_SPRect);
	return true;
}

MyUIListControl::MyUIListControl()
{
}

MyUIListControl::~MyUIListControl()
{
}

bool MyUIListControl::init()
{
	return true;
}

bool MyUIListControl::frame()
{
	for (vector<MyUserInterface*>::iterator::value_type it : m_ButtonList)
	{
		it->frame();
	}

	setPosRect(m_SPRect);
	return true;
}

bool MyUIListControl::render()
{
	preRender();

	MyBaseObject::render();

	for (vector<MyUserInterface*>::iterator::value_type it : m_ButtonList)
	{
		it->render();
	}

	postRender();

	return true;
}

bool MyUIListControl::release()
{
	for (vector<MyUserInterface*>::iterator::value_type it : m_ButtonList)
	{
		it->release();
		delete it;
		it = nullptr;
	}

	m_ButtonList.clear();

	return true;
}
