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

	if (MAININPUT.getKeyState('A') != KEY_FREE)
	{
		m_actionFlag = TRUE;
		m_SPRect.pos.x -= m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_SPRect.pos.x < 0.0f) { m_SPRect.pos.x = 0.0f; }
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

	if (MAININPUT.getKeyState('D') != KEY_FREE)
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
	setTexture(m_stateSpriteSet[m_aState][m_iStateCounter % m_stateSpriteSet[m_aState].size()].c_str());

	updateVertexBuffer();
	return true;
}

MyMovementTestDummy::MyMovementTestDummy()
{
	m_aState = MYPS_IDLE;
	m_moveFlag = false;
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

	m_sup.create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Square.png");
	m_sup.setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f });

	m_fAttackSpeed = 150.0f;
	m_iHitPoint = 100;
	m_iDamage = 1.0f;

	return true;
}

bool MyMovementTestDummy::frame()
{
	m_moveFlag = false;

	MyVector2F temp;

	if (MAININPUT.getKeyState('A'))
	{
		m_moveFlag = true;

		if (MAININPUT.getKeyState(VK_SHIFT))
		{
			if (!(m_aState & MYPS_RUN)) { m_aState |= MYPS_RUN; }
		}
		else
		{
			if (m_aState & MYPS_RUN) { m_aState -= MYPS_RUN; }
		}

		if (m_aState & MYPS_RUN) { m_vVelocity.x = -m_fSpeed *1.5f; }
		else { m_vVelocity.x = -m_fSpeed; }
	}

	if (MAININPUT.getKeyState('D'))
	{
		m_moveFlag = true;
		if (MAININPUT.getKeyState(VK_SHIFT))
		{
			if (!(m_aState & MYPS_RUN)) { m_aState |= MYPS_RUN; }
		}
		else
		{
			if (m_aState & MYPS_RUN) { m_aState -= MYPS_RUN; }
		}

		if (m_aState & MYPS_RUN) { m_vVelocity.x = m_fSpeed * 1.5f; }
		else { m_vVelocity.x = m_fSpeed; }
	}

	if (!m_moveFlag) { m_vVelocity.x = 0.0f; }

	if (MAININPUT.getKeyState(VK_SPACE))
	{
		if (!(m_aState & MYPS_JUMP))
		{
			m_aState |= MYPS_JUMP;
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

	if (boundaryCheck()) { m_aState |= MYPS_JUMP; }

	return true;
}

bool MyMovementTestDummy::postFrame(const MyRect& camRt)
{
	MyRect temp = m_SPRect;
	POINT cursorPt = MAININPUT.getMousePt();
	MyVector2F vDirection = { cursorPt.x - (temp.pos.x - camRt.pos.x + MyWindow::cWidth * 0.5f),
		cursorPt.y - (temp.pos.y - camRt.pos.y + MyWindow::cHeight * 0.5f) };
	vDirection.normalization();

	temp.pos += vDirection * 50.0f;
	temp = { temp.pos, m_sup.getPosRect().fWH };

	m_sup.setDirection(vDirection);
	m_sup.setPosRect(temp);
	m_sup.postFrame(camRt);

	m_prevCSRect = m_CSRect;

	setPosRect(m_SPRect, camRt);
	updateVertexBuffer();
	return true;
}

bool MyMovementTestDummy::render()
{
	m_sup.render();

	preRender();

	if (m_pMaskTexture)
	{
		I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);
	}

	postRender();
	return true;
}

bool MyMovementTestDummy::boundaryCheck()
{
	bool ret = true;

	if (m_SPRect.pos.x < m_boundary.pos.x + m_SPRect.fWH.v[0] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.x = m_boundary.pos.x + m_SPRect.fWH.v[0] * 0.5f;
	}
	if (m_SPRect.pos.x > m_boundary.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.x = m_boundary.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f;
	}
	if (m_SPRect.pos.y < m_boundary.pos.y + m_SPRect.fWH.v[1] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.y = m_boundary.pos.y + m_SPRect.fWH.v[1] * 0.5f;
	}
	if (m_SPRect.pos.y > m_boundary.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.y = m_boundary.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f;
		m_vVelocity.y = 0.0f;
		if (m_aState & MYPS_JUMP) { m_aState -= MYPS_JUMP; }
	}

	return ret;
}

MyVector2F MyMovementTestDummy::staticCollisionHandler(const MyObject2D* pCObj, const MyRect& cRect)
{
	MyRect temp = m_prevCSRect;
	MyRect CObjRect = pCObj->getCollisionRect();
	temp.pos.x = m_CSRect.pos.x;

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.x - m_prevCSRect.pos.x > 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x - m_SPRect.fWH.v[0] * 0.5f - MY_MARGIN_OF_ERROR;
		}
		else if (m_CSRect.pos.x - m_prevCSRect.pos.x < 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x + CObjRect.fWH.v[0] + m_SPRect.fWH.v[0] * 0.5f + MY_MARGIN_OF_ERROR;
		}
	}

	temp = m_prevCSRect;
	temp.pos.y = m_CSRect.pos.y;

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.y - m_prevCSRect.pos.y > 0.0f)
		{
			m_SPRect.pos.y = CObjRect.pos.y - m_SPRect.fWH.v[1] * 0.5f - MY_MARGIN_OF_ERROR;

			if (m_aState & MYPS_JUMP) { m_aState -= MYPS_JUMP; }
			m_vVelocity.y = 0.0f;
		}
		else if (m_CSRect.pos.y - m_prevCSRect.pos.y < 0.0f)
		{
			m_SPRect.pos.y = CObjRect.pos.y + CObjRect.fWH.v[1] + m_SPRect.fWH.v[0] * 0.5f + MY_MARGIN_OF_ERROR;
			m_vVelocity.y = 0.0f;
		}
	}

	return CObjRect.pos + CObjRect.fWH * 0.5f;
}
