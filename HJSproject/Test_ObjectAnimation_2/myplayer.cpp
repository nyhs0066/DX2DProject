#include "myplayer.h"

MyPlayer2D::MyPlayer2D()
{
	m_dState = MYPS_RIGHT;
	m_aState = MYPS_IDLE;
	m_actionFlag = FALSE;
	m_upFlag = FALSE;
	m_fJumpPower = 0.0f;
	stateTimer = 0.0f; 
	stateCounter = 0;
}

MyPlayer2D::~MyPlayer2D()
{
	release();
}

bool MyPlayer2D::init()
{
	m_VPreset.m_stride = sizeof(MyVertex);
	m_VPreset.m_offset = 0;
	m_fSpeed = 300.0f;
	m_fJumpPower = -100.0f;
	m_fMass = 1.0f;

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
			stateCounter = 0;
		}
	}

	if (MAININPUT.getKeyState(VK_RIGHT) != KEY_FREE)
	{
		m_actionFlag = TRUE;
		m_pRect.pos.x += m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_pRect.pos.x > MyWindow::cWidth - m_pRect.fWH.v[0])
		{ 
			m_pRect.pos.x = MyWindow::cWidth - m_pRect.fWH.v[0];
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
			stateCounter = 0;
		}
	}

	if (MAININPUT.getKeyState('Z') != KEY_FREE)
	{
		m_actionFlag = TRUE;
		if (m_aState != MYPS_JUMP)
		{
			m_aState = MYPS_JUMP; 
			stateCounter = 0;
			gravity = { 0.0f, 980.0f };
			setForce(gravity);
			m_upFlag = TRUE;
			m_fElapseJumpTimeCounter = 0.0f;
		}
		if (m_upFlag)
		{
			m_fElapseJumpTimeCounter += 1.0f;
			m_vVelocity.y += m_fJumpPower / m_fElapseJumpTimeCounter;
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

		if (m_pRect.pos.y > (FLOAT)MyWindow::cHeight * 3 / 4 - 50.0f)
		{
			m_pRect.pos.y = (FLOAT)MyWindow::cHeight * 3 / 4 - 50.0f;
			m_actionFlag = FALSE;
			m_vForce.setZeroVector();
			m_vAcceleration.setZeroVector();
			m_vVelocity.setZeroVector();
		}

		setPosRect(m_pRect);
	}

	if (m_aState != MYPS_IDLE && m_actionFlag == FALSE)
	{ 
		m_aState = MYPS_IDLE; 
		stateCounter = 0;
	}

	stateTimer += MAINTIMER.getOneFrameTimeF();

	if (stateTimer > 0.1f) { stateTimer = 0.0f; stateCounter++; }
	setTexture(stateSpriteSet[m_aState][stateCounter % stateSpriteSet[m_aState].size()].c_str());

	updateVertexBuffer();
	return true;
}