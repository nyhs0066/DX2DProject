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
		m_pRect.pos.x -= m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_pRect.pos.x < 0.0f) { m_pRect.pos.x = 0.0f; }
		setPosRect(m_pRect);

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
		m_pRect.pos.x += m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_pRect.pos.x > m_boundary.fWH.v[0] - m_pRect.fWH.v[0])
		{ 
			m_pRect.pos.x = m_boundary.fWH.v[0] - m_pRect.fWH.v[0];
		}
		setPosRect(m_pRect);

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
		m_pRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
		m_vVelocity += m_vAcceleration * dT;

		if (m_pRect.pos.y > (FLOAT)m_boundary.fWH.v[1] * 3 / 4 - 50.0f)
		{
			m_pRect.pos.y = (FLOAT)m_boundary.fWH.v[1] * 3 / 4 - 50.0f;
			m_actionFlag = FALSE;
			m_vForce.setZeroVector();
			m_vAcceleration.setZeroVector();
			m_vVelocity.setZeroVector();
			m_iElapseJumpTimeCounter = 0;
		}

		setPosRect(m_pRect);
	}

	if (m_aState != MYPS_IDLE && m_actionFlag == FALSE)
	{ 
		m_aState = MYPS_IDLE; 
		m_iStateCounter = 0;
	}

	m_fStateTimer += MAINTIMER.getOneFrameTimeF();

	if (m_fStateTimer > 0.1f) { m_fStateTimer = 0.0f; m_iStateCounter++; }
	setTexture(m_stateSpriteSet[m_aState][m_iStateCounter % m_stateSpriteSet[m_aState].size()].c_str());

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
	MyVector2F prevPos = m_pRect.pos;

	m_vAcceleration = m_vForce * (1.0f / m_fMass);
	m_pRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
	m_vVelocity += m_vAcceleration * dT;

	m_vDirection = m_pRect.pos - prevPos;
	m_vDirection.normalization();

	return true;
}

bool MyMovementTestDummy::postframe()
{
	setPosRect(m_pRect);
	updateVertexBuffer();

	return true;
}

void MyMovementTestDummy::collisionHandler(COLLISION_PLANE cPlane, MyObject2D* pCobj)
{
	switch (cPlane)
	{
	case MYCP_LEFT:
	{
		if (!pCobj) { m_pRect.pos.x = m_boundary.fWH.v[0] - m_pRect.fWH.v[0] - 0.1f; }
		else { m_pRect.pos.x = pCobj->getPosRect().pos.x - m_pRect.fWH.v[0] - 0.1f; }
		break;
	}
	case MYCP_RIGHT:
	{
		if (!pCobj) { m_pRect.pos.x = 0.0f + 0.1f; }
		else { m_pRect.pos.x = pCobj->getPosRect().pos.x + pCobj->getPosRect().fWH.v[0]+ 0.1f; }
		break;
	}
	case MYCP_BOT:
	{
		if (!pCobj) { m_pRect.pos.y = 0.0f + 0.1f; }
		else { m_pRect.pos.y = pCobj->getPosRect().pos.y + pCobj->getPosRect().fWH.v[1] + 0.1f; }

		m_vVelocity.y = 0.0f;
		break;
	}
	case MYCP_TOP:
	{
		if (!pCobj) { m_pRect.pos.y = m_boundary.fWH.v[1] - m_pRect.fWH.v[1] - 0.1f; }
		else { m_pRect.pos.y = pCobj->getPosRect().pos.y - m_pRect.fWH.v[1] - 0.1f; }

		m_aState = MYPS_IDLE;
		m_vVelocity.y = 0.0f;
		break;
	}
	default:
		m_aState = MYPS_JUMP; break;
	}
}
