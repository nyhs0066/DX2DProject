#include "myuserinterface.h"

MyUserInterface::MyUserInterface() 
{
	m_UISTsprite = nullptr;
	m_UIMTsprite = nullptr;
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

MyUIButton::MyUIButton()
{
	actionFlag = false;
}

MyUIButton::~MyUIButton()
{
}

bool MyUIButton::frame()
{
	POINT pt = MAININPUT.getMousePt();
	MyVector2F fPt = { (FLOAT)pt.x, (FLOAT)pt.y };
	actionFlag = false;

	if (MyCollision::pointToRect(fPt, m_SPRect))
	{
		UINT input = MAININPUT.getKeyState(VK_LBUTTON);
		if (input)
		{
			m_bState = UB_PUSH;
			if (input == KEY_UP) { actionFlag = true; }
		}
		else { m_bState = UB_SELECT; }
	}
	else { m_bState = UB_IDLE; }

	if (m_UISTsprite) { setTexRect(m_UISTsprite->m_spriteArray[m_bState]); }	
	else { setTexture(m_UIMTsprite->m_spriteArray[m_bState]); }

	setPosRect(m_SPRect);
	return actionFlag;
}
