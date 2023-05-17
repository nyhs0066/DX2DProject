#include "myplayer.h"

MyMovementTestDummy::MyMovementTestDummy()
{
	m_aState = MYPS_IDLE;
	m_moveFlag = false;
	m_upFlag = false;
	m_iExtraJumpNum = 0;
	m_fCurRotateAngle = 0.0f;
	m_fRotateAnglePerSec = 1.0f;
}

MyMovementTestDummy::~MyMovementTestDummy()
{
	release();
}

bool MyMovementTestDummy::init()
{
	m_iMaxHitPoint = 100;
	m_iCurHitPoint = 100;

	m_fSpeed = 300.0f;
	m_fJumpPower = -100.0f;
	m_fMass = 1.0f;
	m_fBlinkDist = 300.0f;
	m_fBlinkTimer = 0.0f;
	MyVector2F gravity = { 0.0f, 1000.0f };
	setForce(gravity);

	m_pShotSound = LOAD_SOUND(L"../../data/sound/laser_shot_8bit.wav");

	m_pSup = new MyObject2D;
	m_pSup->create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Square.png");
	m_pSup->setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f });

	m_pBlinkSup = new MyObject2D;
	m_pBlinkSup->create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Circle.png");
	m_pBlinkSup->setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f });

	m_pRotateSup = new MyObject2D;
	m_pRotateSup->create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Triangle.png");
	m_pRotateSup->setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f});

	m_fAttackSpeed = 10.0f;
	m_iCurHitPoint = 100;
	m_iDamage = 1.0f;

	m_fHitTimer = 0.0f;

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
			if (m_aState & MYPS_RUN) { m_aState &= ~MYPS_RUN; }
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
			if (m_aState & MYPS_RUN) { m_aState &= ~MYPS_RUN; }
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
			m_fElapseJumpTime = 1.0f;
			m_upFlag = TRUE;
		}
		else if((m_iExtraJumpNum > 0) && !m_upFlag)
		{
            m_fElapseJumpTime = 1.0f;
			m_upFlag = TRUE;
			m_iExtraJumpNum--;
			m_vVelocity.y = 0.0f;
		}
		if (m_upFlag)
		{
			FLOAT temp = m_fElapseJumpTime;
			m_fElapseJumpTime += MAINTIMER.getOneFrameTimeF();
			m_vVelocity.y += m_fJumpPower * (seq(m_fElapseJumpTime * 1000 - 1000) - seq(temp * 1000 - 1000));
		}
	}
	else { m_upFlag = FALSE; }

	FLOAT dT = MAINTIMER.getOneFrameTimeF();
	MyVector2F prevPos = m_SPRect.pos;

	m_fBlinkTimer += dT;
	if (MAININPUT.getKeyState(VK_RBUTTON) == KEY_DOWN)
	{
		if (m_fBlinkTimer > 10.0f)
		{
			m_SPRect.pos = m_pBlinkSup->m_SPRect.pos;
			m_fBlinkTimer = 0.0f;
			m_vVelocity.y = 0.0f;
		}
	}

	m_vAcceleration = m_vForce * (1.0f / m_fMass);
	m_SPRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
	m_vVelocity += m_vAcceleration * dT;

	adjustCRect(m_SPRect);

	m_vDirection = m_SPRect.pos - prevPos;
	m_vDirection.normalization();

	if (boundaryCheck()) { m_aState |= MYPS_JUMP; }

	return true;
}

bool MyMovementTestDummy::postFrame(const MyExRect& camRt, FLOAT radian)
{
	m_prevCSRect = m_CSRect;

	m_fCurRotateAngle += m_fRotateAnglePerSec * MAINTIMER.getOneFrameTimeF();
	MyObject2D::postFrame(camRt, m_fCurRotateAngle);

	//sup
	MyExRect temp = m_SPRect;
	POINT cPt = MAININPUT.getMousePt();
	MyVector2F cursorPt = { (FLOAT)cPt.x , (FLOAT)cPt.y };
	MyVector2F scrPt;
	scrPt.x = m_SPRect.pos.x - camRt.pos.x + MyWindow::cWidth * 0.5f;
	scrPt.y = m_SPRect.pos.y - camRt.pos.y + MyWindow::cHeight * 0.5f;
	MyVector2F vDirection = cursorPt - scrPt;
	vDirection.normalization();

	temp = { temp.pos + vDirection * 50.0f , m_pSup->m_SPRect.fWH };

	m_pSup->setDirection(vDirection);
	m_pSup->setPosRect(temp);
	m_pSup->postFrame(camRt);

	temp.pos -= vDirection * 50.0f;

	//blink sup
	if (MyVector2F::getDistance(cursorPt, scrPt) <= MyVector2F::getDistance(temp.pos + vDirection * m_fBlinkDist, m_SPRect.pos))
	{
		temp = { temp.pos + cursorPt - scrPt, m_pBlinkSup->m_SPRect.fWH };
	}
	else { temp = { temp.pos + vDirection * m_fBlinkDist , m_pBlinkSup->m_SPRect.fWH }; }

	m_pBlinkSup->setDirection(vDirection);
	m_pBlinkSup->setPosRect(temp);
	m_pBlinkSup->postFrame(camRt);

	//rotate sup
	MyVector2F vDir;
	m_pRotateSup->m_SPRect.pos = m_SPRect.pos + MyVector2F(100.0f, 100.0f);
	m_pRotateSup->arbitRotation(m_SPRect.pos, m_fCurRotateAngle);
	vDir = m_pRotateSup->m_SPRect.pos - m_SPRect.pos;
	vDir.normalization();
	m_pRotateSup->setDirection(vDir);
	m_pRotateSup->postFrame(camRt);

	//hit action
	m_fHitTimer += MAINTIMER.getOneFrameTimeF();

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 1.0f, 1.0f, 1.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");

		m_fHitTimer -= FIXFRAMET;
	}

	return true;
}

bool MyMovementTestDummy::render()
{
	m_pSup->render();
	if (m_fBlinkTimer >= 10.0f) { m_pBlinkSup->render(); }
	m_pRotateSup->render();

	preRender();

	if (m_pMaskTexture)
	{
		I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);
	}

	postRender();
	return true;
}

bool MyMovementTestDummy::release()
{
	if (m_pSup) { m_pSup->release(); delete m_pSup; m_pSup = nullptr; }
	if (m_pBlinkSup) { m_pBlinkSup->release(); delete m_pBlinkSup; m_pBlinkSup = nullptr; }
	if (m_pRotateSup) { m_pRotateSup->release(); delete m_pRotateSup; m_pRotateSup = nullptr; }

	return true;
}

bool MyMovementTestDummy::boundaryCheck()
{
	bool ret = true;

	if (m_SPRect.pos.x < m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.x = m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f;
	}
	if (m_SPRect.pos.x > m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.x = m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f;
	}
	if (m_SPRect.pos.y < m_BRect.pos.y + m_SPRect.fWH.v[1] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.y = m_BRect.pos.y + m_SPRect.fWH.v[1] * 0.5f;
	}
	if (m_SPRect.pos.y > m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.y = m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f - 0.0003f;
		m_vVelocity.y = 0.0f;
		if (m_aState & MYPS_JUMP) { m_aState &= ~MYPS_JUMP; m_iExtraJumpNum = MAX_EXTRA_JUMP_COUNT; }
	}

	adjustCRect(m_SPRect);

	return ret;
}

void MyMovementTestDummy::setRotateSpeed(FLOAT fRSpeed)
{
	m_fRotateAnglePerSec = fRSpeed;
}

void MyMovementTestDummy::playShotSound()
{
	m_pShotSound->playEffect();
	m_pShotSound->volumeDown(80);
}

void MyMovementTestDummy::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MYRND_FRANGE(0.0f, 1.0f);

	MyEffect* newE = new MyProjectile;
	*newE = *pEffectPreset;
	newE->m_SPRect.pos = m_pSup->m_SPRect.pos;
	newE->setDirectionAndSpeed(m_pSup->getDirection(), 350.0f, 0.0f);
	newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };
	newE->m_iDamage = m_iDamage;

	effectList.push_back(newE);
}

FLOAT MyMovementTestDummy::seq(int k)
{
	FLOAT ret = 0;

	if (k <= 2000) { for (int i = 1; i <= k; i++) { ret += 1.0f / i; } }
	else
	{
		for (int i = 1; i <= 2000; i++) { ret += 1.0f / i; }
		ret += 1.0f * (k - 2000) / 2000.0f;
	}

	return ret;
}

MyVector2F MyMovementTestDummy::staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect)
{
	MyExRect temp = m_prevCSRect;
	MyExRect CObjRect = pCObj->getCSRect();
	temp.pos.x = m_CSRect.pos.x;

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.x - m_prevCSRect.pos.x > 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x - m_SPRect.fWH.v[0] * 0.5f - 0.001f;
		}
		else if (m_CSRect.pos.x - m_prevCSRect.pos.x < 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x + CObjRect.fWH.v[0] + m_SPRect.fWH.v[0] * 0.5f + 0.001f;
		}
	}

	temp = m_prevCSRect;
	temp.pos.y = m_CSRect.pos.y;
	

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.y - m_prevCSRect.pos.y > 0.0f)
		{
			m_SPRect.pos.y = CObjRect.pos.y - m_SPRect.fWH.v[1] * 0.5f - 0.0003f;
			m_vVelocity.y = 0.0f;
			if (m_aState & MYPS_JUMP) { m_aState &= ~MYPS_JUMP; m_iExtraJumpNum = MAX_EXTRA_JUMP_COUNT; }
			
		}
		else if (m_CSRect.pos.y - m_prevCSRect.pos.y < 0.0f)
		{
			m_SPRect.pos.y = CObjRect.pos.y + CObjRect.fWH.v[1] + m_SPRect.fWH.v[0] * 0.5f + 0.001f;
			m_vVelocity.y = 0.0f;
		}
	}

	adjustCRect(m_SPRect);

	return CObjRect.pos + CObjRect.fWH * 0.5f;
}

MyVector2F MyMovementTestDummy::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& cRect)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_iCurHitPoint = m_iMaxHitPoint; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}

MyVector2F MyMovementTestDummy::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect)
{
	
	return MyVector2F();
}
