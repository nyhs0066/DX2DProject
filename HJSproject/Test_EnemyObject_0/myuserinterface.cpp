#include "myuserinterface.h"

MyUserInterface::MyUserInterface()
{
	m_pSprite = nullptr;

	m_bState = UB_DISABLE;
}

MyUserInterface::~MyUserInterface()
{
	release();
}

bool MyUserInterface::create(wstring wszShaderName, wstring wszTextureName)
{
	if (!MyObject2D::create(wszShaderName, wszTextureName)) { return false; }

	this->wszShaderName = wszShaderName;
	this->wszTextureName = wszTextureName;
	return true;
}

void MyUserInterface::rotate(FLOAT rad, MyVector2F pivot)
{
	FLOAT tx = m_SPRect.pos.x - pivot.x;
	FLOAT ty = m_SPRect.pos.y - pivot.y;

	m_SPRect.pos.x = cosf(rad) * tx - sinf(rad) * ty + pivot.x;
	m_SPRect.pos.y = sinf(rad) * tx + cosf(rad) * ty + pivot.y;
}

bool MyUserInterface::setSprite(wstring wszSpriteName)
{
	if (m_pSprite = GET_SPRITE(wszSpriteName)) { return true; }

	if (m_pSprite->m_rtSpriteArray.size())
	{
		setTexRect(m_pSprite->m_rtSpriteArray[0]);
	}
	else
	{
		setTexRect(m_pSprite->m_texSpriteArray[0]->m_TRect);
	}

	return false;
}

void MyUserInterface::partition(FLOAT factorLX, FLOAT factorRX,
	FLOAT factorTY, FLOAT factorBY,
	FLOAT factorLTX, FLOAT factorRTX,
	FLOAT factorTTY, FLOAT factorBTY)
{
	m_pParts.resize(9);

	FLOAT fX[4], fY[4], fU[4], fV[4];
	fX[0] = m_SPRect.pos.x;
	fX[1] = m_SPRect.pos.x + m_SPRect.fWH.x * factorLX;
	fX[2] = m_SPRect.pos.x + m_SPRect.fWH.x - m_SPRect.fWH.x * factorRX;
	fX[3] = m_SPRect.pos.x + m_SPRect.fWH.x;

	fY[0] = m_SPRect.pos.y;
	fY[1] = m_SPRect.pos.y + m_SPRect.fWH.y * factorTY;
	fY[2] = m_SPRect.pos.y + m_SPRect.fWH.y - m_SPRect.fWH.y * factorBY;
	fY[3] = m_SPRect.pos.y + m_SPRect.fWH.y;

	fU[0] = m_TRect.pos.x;
	fU[1] = m_TRect.pos.x + m_TRect.fWH.x * factorLTX;
	fU[2] = m_TRect.pos.x + m_TRect.fWH.x - m_TRect.fWH.x * factorRTX;
	fU[3] = m_TRect.pos.x + m_TRect.fWH.x;

	fV[0] = m_TRect.pos.y;
	fV[1] = m_TRect.pos.y + m_TRect.fWH.y * factorTTY;
	fV[2] = m_TRect.pos.y + m_TRect.fWH.y - m_TRect.fWH.y * factorBTY;
	fV[3] = m_TRect.pos.y + m_TRect.fWH.y;

	MyExRect posRt;
	MyExRect texRt;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			posRt = { fX[j], fY[i], fX[j + 1] - fX[j], fY[i + 1] - fY[i] };
			texRt = { fU[j], fV[i], fU[j + 1] - fU[j], fV[i + 1] - fV[i] };
			m_pParts[i * 3 + j] = new MyUserInterface;
			m_pParts[i * 3 + j]->create(wszShaderName, wszTextureName);
			m_pParts[i * 3 + j]->setPosRect(posRt);
			m_pParts[i * 3 + j]->setTexRect(texRt);
		}
	}
}

bool MyUserInterface::addChild(MyUserInterface* pUI)
{
	m_pChildren.push_back(pUI);

	return true;
}

bool MyUserInterface::release()
{
	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	m_pParts.clear();

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		it->release();
		delete it;
		it = nullptr;
	}
	m_pChildren.clear();

	return true;
}

MyUIButton::MyUIButton() {}

MyUIButton::~MyUIButton()
{
	release();
}

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

	if (m_pSprite->m_rtSpriteArray.size())
	{
		if (m_bState == UB_SELECT) { setTexRect(m_pSprite->m_rtSpriteArray[UB_PUSH]); }
		else { setTexRect(m_pSprite->m_rtSpriteArray[m_bState]); }
	}
	else
	{
		if (m_bState == UB_SELECT) { setTexture(m_pSprite->m_texSpriteArray[UB_PUSH]); }
		else 
		{ 
			setTexture(m_pSprite->m_texSpriteArray[m_bState]); 
			setTexRect(m_pSprite->m_texSpriteArray[m_bState]->m_TRect);
		}
	}

	MyExRect temp;

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	return true;
}

bool MyUIButton::render()
{
	MyObject2D::render();

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		it->render();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		it->render();
	}

	return true;
}

MyUIListControl::MyUIListControl()
{
}

MyUIListControl::~MyUIListControl()
{
	release();
}

bool MyUIListControl::init()
{
	return true;
}

bool MyUIListControl::frame()
{
	MyExRect temp;

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}
	return true;
}

bool MyUIListControl::render()
{
	MyObject2D::render();

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		it->render();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		it->render();
	}
	return true;
}


MyUIDialog::MyUIDialog()
{
	m_bDragFlag = FALSE;
}

MyUIDialog::~MyUIDialog()
{
	release();
}

bool MyUIDialog::init()
{
	return true;
}

bool MyUIDialog::frame()
{
	POINT pt = MAININPUT.getMousePt();
	MyVector2F fPt = { (FLOAT)pt.x, (FLOAT)pt.y };

	if (MyCollision::pointToRect(fPt, m_SPRect))
	{
		UINT input = MAININPUT.getKeyState(VK_LBUTTON);
		
		if (input == KEY_DOWN)
		{
			m_bDragFlag = TRUE;
			m_vLastMPt = fPt;
		}
		if (m_bDragFlag && input == KEY_HOLD)
		{
			MyVector2F offset = fPt - m_vLastMPt;
			m_vLastMPt = fPt;
			m_SPRect.pos += offset;
			m_posOffset = offset;
		}
		if (input == KEY_UP)
		{
			m_bDragFlag = FALSE;
			m_posOffset = { 0.0f, 0.0f };
		}
	}
	else { m_posOffset = { 0.0f, 0.0f }; m_bDragFlag = FALSE; }

	MyExRect temp;

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	return true;
}

bool MyUIDialog::render()
{
	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		it->render();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		it->render();
	}

	return true;
}

MyUIChargeBar::MyUIChargeBar()
{
	m_fCurX = 0.0f;
	m_fPosW = m_fTexW = 0.0f;
}

MyUIChargeBar::~MyUIChargeBar()
{
	release();
}

bool MyUIChargeBar::init()
{
	m_fPosW = m_SPRect.fWH.x;
	m_fTexW = m_TRect.fWH.x;

	m_SPRect.fWH.x = 0.0f;
	m_TRect.fWH.x = 0.0f;

	return true;
}

bool MyUIChargeBar::frame()
{
	if (MAININPUT.getKeyState(VK_RBUTTON))
	{
		m_fCurX += 50.0f * MAINTIMER.getOneFrameTimeF();
		if (m_fCurX > m_fPosW) { m_fCurX = m_fPosW; }
	}
	else
	{
		m_fCurX -= 50.0f * MAINTIMER.getOneFrameTimeF();
		if (m_fCurX < 0.0f) { m_fCurX = 0.0f; }
	}

	setPosRect({ m_SPRect.pos,  {m_fCurX, m_SPRect.fWH.y} });
	setTexRect({ 0.0f, 0.0f, m_fTexW * m_fCurX / m_fPosW, m_TRect.fWH.y });

	MyExRect temp;

	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->m_posOffset = m_posOffset;
		it->frame();
		it->postFrame();
	}

	return true;
}

bool MyUIChargeBar::render()
{
	for (vector<MyUserInterface*>::iterator::value_type it : m_pParts)
	{
		it->render();
	}

	for (vector<MyUserInterface*>::iterator::value_type it : m_pChildren)
	{
		it->render();
	}

	MyObject2D::render();

	return true;
}