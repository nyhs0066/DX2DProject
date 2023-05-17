#include "myplayer.h"

MyPlayer2D::MyPlayer2D()
{
	m_dState = MYPS_RIGHT;
	m_aState = MYPS_IDLE;
	m_actionFlag = FALSE;
	m_upFlag = FALSE;
	m_fJumpPower = 0.0f;
	m_iElapseJumpTimeCounter = 0;
	m_fStateTimer = 0.0f; 
	m_iStateCounter = 0;
}

MyPlayer2D::~MyPlayer2D()
{
	release();
}

bool MyPlayer2D::addSprite(wstring wszSpriteName)
{
	MyMultiTextureSprite* temp = GET_MT_SPRITE(wszSpriteName);

	if (temp)
	{ 
		m_stateSpriteSet.push_back(GET_MT_SPRITE(wszSpriteName)); 
		return true;
	}

	return false;
}

bool MyPlayer2D::init()
{
	m_fSpeed = 300.0f;
	m_fMass = 1.0f;
	m_fJumpPower = -100.0f;

	return true;
}

bool MyPlayer2D::frame()
{
	m_actionFlag = FALSE;
	MyVector2F gravity;

	if (MAININPUT.getKeyState(VK_LEFT) != KEY_FREE) 
	{
		m_actionFlag = TRUE;
		m_SPRect.pos.x -= m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_SPRect.pos.x < m_boundary.pos.x) { m_SPRect.pos.x = m_boundary.pos.x; }
		setPosRect(m_SPRect);

		if (m_dState != MYPS_LEFT)
		{
			m_dState = MYPS_LEFT;
			m_tRect.pos.x = m_tRect.fWH.v[0];
			m_tRect.fWH.v[0] = -m_tRect.fWH.v[0];
			setTexRect(m_tRect);
		}

		if (m_aState == MYPS_IDLE)
		{
			m_aState = MYPS_WALK;
			m_iStateCounter = 0;
		}
	}

	if (MAININPUT.getKeyState(VK_RIGHT) != KEY_FREE)
	{
		m_actionFlag = TRUE;
		m_SPRect.pos.x += m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_SPRect.pos.x > m_boundary.fWH.v[0] - m_SPRect.fWH.v[0])
		{ 
			m_SPRect.pos.x = m_boundary.fWH.v[0] - m_SPRect.fWH.v[0];
		}
		setPosRect(m_SPRect);

		if (m_dState != MYPS_RIGHT)
		{
			m_dState = MYPS_RIGHT;
			m_tRect.pos.x = 0;
			m_tRect.fWH.v[0] = -m_tRect.fWH.v[0];
			setTexRect(m_tRect);
		}

		if (m_aState == MYPS_IDLE)
		{
			m_aState = MYPS_WALK;
			m_iStateCounter = 0;
		}
	}

	if (MAININPUT.getKeyState('Z') != KEY_FREE)
	{
		m_actionFlag = TRUE;
		if (m_aState != MYPS_JUMP)
		{
			m_aState = MYPS_JUMP; 
			m_iStateCounter = 0;
			gravity = { 0.0f, 980.0f };
			setForce(gravity);
			m_upFlag = TRUE;
		}
		if (m_upFlag)
		{
			m_iElapseJumpTimeCounter++;
			m_vVelocity.y += m_fJumpPower / m_iElapseJumpTimeCounter;
		}
	}
	else if (m_upFlag) { m_upFlag = FALSE; }
	
	if(m_aState == MYPS_JUMP)
	{
		m_actionFlag = TRUE;

		FLOAT dT = MAINTIMER.getOneFrameTimeF();

		m_vAcceleration = m_vForce * (1.0f / m_fMass);
		m_SPRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
		m_vVelocity += m_vAcceleration * dT;

		if (m_SPRect.pos.y > (FLOAT)m_boundary.fWH.v[1] * 3 / 4 - 50.0f)
		{
			m_SPRect.pos.y = (FLOAT)m_boundary.fWH.v[1] * 3 / 4 - 50.0f;
			m_actionFlag = FALSE;
			m_vForce.setZeroVector();
			m_vAcceleration.setZeroVector();
			m_vVelocity.setZeroVector();
			m_iElapseJumpTimeCounter = 0;
		}

		setPosRect(m_SPRect);
	}

	if (m_aState != MYPS_IDLE && m_actionFlag == FALSE)
	{ 
		m_aState = MYPS_IDLE; 
		m_iStateCounter = 0;
	}

	m_fStateTimer += MAINTIMER.getOneFrameTimeF();

	if (m_fStateTimer > 0.1f) { m_fStateTimer = 0.0f; m_iStateCounter++; }
	
	setTexture(m_stateSpriteSet[m_aState]->m_spriteArray[m_iStateCounter % (m_stateSpriteSet[m_aState]->m_spriteArray.size())]);

	updateVertexBuffer();
	return true;
}

MyMovementTestDummy::MyMovementTestDummy()
{
	m_aState = MYPS_IDLE;
	moveFlag = false;
}

MyMovementTestDummy::~MyMovementTestDummy()
{
	
}

bool MyMovementTestDummy::init()
{
	m_VPreset.m_stride = sizeof(MyVertex);
	m_VPreset.m_offset = 0;
	m_fSpeed = 300.0f;
	m_fMass = 1.0f;
	MyVector2F gravity = { 0.0f, 1000.0f };
	setForce(gravity);

	return true;
}

bool MyMovementTestDummy::frame()
{
	MyVector2F temp;
	moveFlag = false;

	if (MAININPUT.getKeyState(VK_LEFT) != KEY_FREE)
	{
		moveFlag = true;
		m_vVelocity.x = -m_fSpeed;
	}

	if (MAININPUT.getKeyState(VK_RIGHT) != KEY_FREE)
	{
		moveFlag = true;
		m_vVelocity.x = m_fSpeed;
	}

	if (!moveFlag) { m_vVelocity.x = 0.0f; }

	if (MAININPUT.getKeyState('Z') != KEY_FREE)
	{
		if (m_aState != MYPS_JUMP)
		{
			m_aState = MYPS_JUMP;
			m_vVelocity = { 0.0f, -600.0f };
		}
	}

	FLOAT dT = MAINTIMER.getOneFrameTimeF();
	MyVector2F prevPos = m_SPRect.pos;

	m_vAcceleration = m_vForce * (1.0f / m_fMass);
	m_SPRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
	m_vVelocity += m_vAcceleration * dT;

	m_vDirection = m_SPRect.pos - prevPos;
	m_vDirection.normalization();

	return true;
}

bool MyMovementTestDummy::boundaryCheck()
{
	bool cFlag = false;

	if (m_SPRect.pos.x <= m_boundary.pos.x + m_SPRect.fWH.v[0] * 0.5f)
	{
		cFlag = true;
		collisionHandler(MYCP_RIGHT);
	}
	if (m_SPRect.pos.x >= m_boundary.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f)
	{
		cFlag = true;
		collisionHandler(MYCP_LEFT);
	}
	if (m_SPRect.pos.y <= m_boundary.pos.y + m_SPRect.fWH.v[1] * 0.5f)
	{
		cFlag = true;
		collisionHandler(MYCP_BOT);
	}
	if (m_SPRect.pos.y >= m_boundary.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		cFlag = true;
		collisionHandler(MYCP_TOP);
	}

	return cFlag;
}

void MyMovementTestDummy::collisionHandler(const COLLISION_PLANE cPlane, const MyObject2D* pCobj)
{
	switch (cPlane)
	{
	case MYCP_LEFT:
	{
		if (!pCobj) { m_SPRect.pos.x = m_boundary.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f - 0.1f; }
		else { m_SPRect.pos.x = pCobj->getPosRect().pos.x - m_SPRect.fWH.v[0] - 0.1f; }
		break;
	}
	case MYCP_RIGHT:
	{
		if (!pCobj) { m_SPRect.pos.x = 0.0f + m_SPRect.fWH.v[0] * 0.5f + 0.1f; }
		else { m_SPRect.pos.x = pCobj->getPosRect().pos.x + pCobj->getPosRect().fWH.v[0] + 0.1f; }
		break;
	}
	case MYCP_BOT:
	{
		if (!pCobj) { m_SPRect.pos.y = 0.0f + m_SPRect.fWH.v[1] * 0.5f + 0.1f; }
		else { m_SPRect.pos.y = pCobj->getPosRect().pos.y + pCobj->getPosRect().fWH.v[1] + 0.1f; }

		m_vVelocity.y = 0.0f;
		break;
	}
	case MYCP_TOP:
	{
		if (!pCobj) { m_SPRect.pos.y = m_boundary.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f - 0.1f; }
		else { m_SPRect.pos.y = pCobj->getPosRect().pos.y - m_SPRect.fWH.v[1] - 0.1f; }

		m_aState = MYPS_IDLE;
		m_vVelocity.y = 0.0f;
		break;
	}
	}
}

void MyMovementTestDummy::setAerial()
{
	m_aState = MYPS_JUMP;
}
