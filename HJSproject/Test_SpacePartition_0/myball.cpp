#include "myball.h"

bool MyBall::init()
{
	m_fSpeed = 700.0f;

	MYRND_FRANGE(1.0f, 10.0f);
	m_fMass = MYRND.getF();

	MYRND_FRANGE(-1.0f, 1.0f);
	m_vDirection = { MYRND.getF() , MYRND.getF() };

	return true;
}

bool MyBall::frame()
{
	m_SPRect.pos += m_vDirection * m_fSpeed * MAINTIMER.getOneFrameTimeF() * (1.0f / m_fMass);

	if (m_SPRect.pos.x < m_boundary.pos.x + m_SPRect.fWH.x * 0.5f)
	{
		m_SPRect.pos.x = m_boundary.pos.x + m_SPRect.fWH.x * 0.5f;
		m_vDirection.x = -m_vDirection.x;
	}
	if (m_SPRect.pos.x > m_boundary.pos.x + m_boundary.fWH.x - m_SPRect.fWH.x * 0.5f)
	{
		m_SPRect.pos.x = m_boundary.pos.x + m_boundary.fWH.x - m_SPRect.fWH.x * 0.5f;
		m_vDirection.x = -m_vDirection.x;
	}
	if (m_SPRect.pos.y < m_boundary.pos.y + m_SPRect.fWH.y * 0.5f)
	{
		m_SPRect.pos.y = m_boundary.pos.y + m_SPRect.fWH.y * 0.5f;
		m_vDirection.y = -m_vDirection.y;
	}
	if (m_SPRect.pos.y > m_boundary.pos.y + m_boundary.fWH.y - m_SPRect.fWH.y * 0.5f)
	{
		m_SPRect.pos.y = m_boundary.pos.y + m_boundary.fWH.y - m_SPRect.fWH.y * 0.5f;
		m_vDirection.y = -m_vDirection.y;
	}

	return true;
}

bool MyBall::create(MyRect bRect)
{
	HRESULT hr = S_OK;

	MyRect pRect = { {(FLOAT)MyWindow::cWidth / 2 - 2.5f * 3, (FLOAT)MyWindow::cHeight / 2 }, { 5 * 3, 4 * 3}};
	MyRect tRect = { { 40.0f, 0.0f }, { 5.0f, 4.0f } };

	m_pMaskTexture = LOAD_TEXTURE(L"../../data/arkanoid/nes_arkanoid_vaus_mask.png");
	if (!m_pMaskTexture) { return false; }

	if (!MyObject2D::create(L"../../data/shader/mydefaultmaskshader.txt", L"../../data/arkanoid/nes_arkanoid_vaus.png",
		pRect, tRect, bRect)) 
	{
		return false;
	}

	return true;
}
