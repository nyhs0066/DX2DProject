#include "myplayer.h"

MyPlayer2D::MyPlayer2D()
{
	m_dState = MYPS_RIGHT;
	m_aState = MYPS_IDLE;
	inputFlag = FALSE;
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

	return true;
}

bool MyPlayer2D::frame()
{
	inputFlag = FALSE;

	if (MAININPUT.getKeyState(VK_LEFT) != KEY_FREE) 
	{
		inputFlag = TRUE;
		m_pRect.pos.x -= m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_pRect.pos.x < 24.0f) { m_pRect.pos.x = 24.0f; }
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
		inputFlag = TRUE;
		m_pRect.pos.x += m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_pRect.pos.x > MyWindow::cWidth - 24.0f - m_pRect.fWH.v[0])
		{ 
			m_pRect.pos.x = MyWindow::cWidth - 24.0f - m_pRect.fWH.v[0];
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

	if (m_aState != MYPS_IDLE && inputFlag == FALSE)
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