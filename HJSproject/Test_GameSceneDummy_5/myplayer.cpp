#include "myplayer.h"

MyPlayer2D::MyPlayer2D()
{
	m_aState = MYPS_IDLE;
	m_moveFlag = false;
	m_upFlag = false;
	m_bHitFlag = false;
	m_iExtraJumpNum = 0;
	m_fCurRotateAngle = 0.0f;
	m_fBlinkTimer = 0.0f;
	m_fRotateAnglePerSec = 0.0f;
	m_fFlickerTimer = 0.0f;
	m_bInputNullifyFlag = false;
	m_fElapseJumpTime = 0.0f;
	m_fRegenTimer = 0.0f;
}

MyPlayer2D::~MyPlayer2D()
{
	release();
}

bool MyPlayer2D::init()
{
	m_iMaxHitPoint = 175;
	m_iCurHitPoint = 175;

	m_fSpeed = 300.0f;
	m_fJumpPower = -100.0f;
	m_fMass = 1.0f;
	m_fBlinkDist = 400.0f;
	
	MyVector2F gravity = { 0.0f, 1000.0f };
	setForce(gravity);

	m_pShotSound = LOAD_SOUND(L"../../data/sound/laser_shot_8bit.wav");
	m_pHitSound = LOAD_SOUND(L"../../data/sound/player_hit.wav");

	m_sup.create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Square.png");
	m_sup.setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f });

	m_blinkSup.create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Circle.png");
	m_blinkSup.setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f });

	m_rotateSup.create(L"../../data/shader/mydefaultshader.txt", L"../../data/shapes/Triangle.png");
	m_rotateSup.setPosRect({ m_SPRect.pos, m_SPRect.fWH * 0.2f});

	m_HPBar.create(L"../../data/shader/mydefaultshader.txt", this);

	m_fAttackSpeed = 5.0f;
	m_iDamage = 4;

	m_fInvincibliltyTime = 2.0f;
	m_fInputNullifyTime = 0.75f;

	m_fHitTimer = m_fInvincibliltyTime;

	m_weaponType = 1;

	m_iAttackGrade = 0;
	m_iArrackSpeedGrade = 0;
	m_iHpGen = 0;

	return true;
}

bool MyPlayer2D::frame()
{
	FLOAT deltaT = MAINTIMER.getOneFrameTimeF();

	m_fRegenTimer += deltaT;

	if (m_fRegenTimer > 1.0f)
	{
		m_fRegenTimer -= 1.0f;
		m_iCurHitPoint += m_iHpGen;

		if (m_iCurHitPoint > m_iMaxHitPoint) { m_iCurHitPoint = m_iMaxHitPoint; }
	}

	if (m_bHitFlag)
	{
		m_fHitTimer += deltaT;

		if (m_fHitTimer > FIXFRAMET)
		{
			m_fFlickerTimer += deltaT;
			if (m_fFlickerTimer > FIXFRAMET*2)
			{
				m_fFlickerTimer -= FIXFRAMET*2;
				m_iFlickerCount++;
			}

			if (m_iFlickerCount % 2)
			{
				setColors({ 0.2f, 0.2f, 0.2f, 1.0f });
			}
			else
			{
				setColors({ 0.4f, 0.4f, 0.4f, 1.0f });
			}
			
			setShader(L"../../data/shader/mydefaultshader.txt");
		}

		if (m_fHitTimer > m_fInputNullifyTime) { m_bInputNullifyFlag = FALSE; }
		if (m_fHitTimer > m_fInvincibliltyTime) 
		{ 
			m_bHitFlag = FALSE;
			setColors({ 1.0f, 1.0f, 1.0f, 1.0f });
			setShader(L"../../data/shader/mydefaultshader.txt");
			m_fFlickerTimer = 0.0f;
			m_iFlickerCount = 0;
		}
	}

	m_moveFlag = false;
	MyVector2F temp;
	MyVector2F prevPos = m_SPRect.pos;

	if (MAININPUT.getKeyState('A') && !m_bInputNullifyFlag)
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

		if (m_aState & MYPS_RUN) { m_vVelocity.x = -m_fSpeed * 1.5f; }
		else { m_vVelocity.x = -m_fSpeed; }
	}

	if (MAININPUT.getKeyState('D') && !m_bInputNullifyFlag)
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

	if (!m_moveFlag && !m_bInputNullifyFlag) { m_vVelocity.x = 0.0f; }
	if (m_bInputNullifyFlag) { m_vVelocity.x = m_vVelocity.x * 0.99f; }

	if (MAININPUT.getKeyState(VK_SPACE) && !m_bInputNullifyFlag)
	{
		if (!(m_aState & MYPS_JUMP))
		{
			m_aState |= MYPS_JUMP;
			m_fElapseJumpTime = 1.0f;
			m_upFlag = TRUE;
		}
		else if ((m_iExtraJumpNum > 0) && !m_upFlag)
		{
			m_fElapseJumpTime = 1.0f;
			m_upFlag = TRUE;
			m_iExtraJumpNum--;
			m_vVelocity.y = 0.0f;
		}
		if (m_upFlag)
		{
			FLOAT temp = m_fElapseJumpTime;
			m_fElapseJumpTime += deltaT;
			m_vVelocity.y += m_fJumpPower * (seq(m_fElapseJumpTime * 1000 - 1000) - seq(temp * 1000 - 1000));
		}
	}
	else { m_upFlag = FALSE; }

	m_fBlinkTimer += deltaT;
	if (MAININPUT.getKeyState(VK_RBUTTON) == KEY_DOWN && !m_bInputNullifyFlag)
	{
		if (m_fBlinkTimer > 5.0f)
		{
			m_SPRect.pos = m_blinkSup.m_SPRect.pos;
			m_fBlinkTimer = 0.0f;
			m_vVelocity.y = 0.0f;
		}
	}

	m_vAcceleration = m_vForce * (1.0f / m_fMass);
	m_SPRect.pos += m_vVelocity * deltaT + m_vAcceleration * deltaT * deltaT * 0.5f;
	m_vVelocity += m_vAcceleration * deltaT;

	adjustCRect(m_SPRect);

	m_vDirection = m_SPRect.pos - prevPos;
	m_vDirection.normalization();

	if (boundaryCheck()) { m_aState |= MYPS_JUMP; }

	return true;
}

bool MyPlayer2D::postFrame(const MyExRect& camRt, FLOAT radian)
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

	temp = { temp.pos + vDirection * 50.0f , m_sup.m_SPRect.fWH };

	m_sup.setDirection(vDirection);
	m_sup.setPosRect(temp);
	m_sup.postFrame(camRt);

	temp.pos -= vDirection * 50.0f;

	//blink sup
	if (MyVector2F::getDistance(cursorPt, scrPt) <= MyVector2F::getDistance(temp.pos + vDirection * m_fBlinkDist, m_SPRect.pos))
	{
		temp = { temp.pos + cursorPt - scrPt, m_blinkSup.m_SPRect.fWH };
	}
	else { temp = { temp.pos + vDirection * m_fBlinkDist , m_blinkSup.m_SPRect.fWH }; }

	m_blinkSup.setDirection(vDirection);
	m_blinkSup.setPosRect(temp);
	m_blinkSup.postFrame(camRt);

	//rotate sup
	MyVector2F vDir;
	m_rotateSup.m_SPRect.pos = m_SPRect.pos + MyVector2F(100.0f, 100.0f);
	m_rotateSup.arbitRotation(m_SPRect.pos, m_fCurRotateAngle);
	vDir = m_rotateSup.m_SPRect.pos - m_SPRect.pos;
	vDir.normalization();
	m_rotateSup.setDirection(vDir);
	m_rotateSup.postFrame(camRt);

	m_HPBar.postFrame(camRt);
	return true;
}

bool MyPlayer2D::render()
{
	m_sup.render();
	if (m_fBlinkTimer >= 10.0f) { m_blinkSup.render(); }
	m_rotateSup.render();
	m_HPBar.render();

	preRender();

	if (m_pMaskTexture)
	{
		I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);
	}

	postRender();
	return true;
}

bool MyPlayer2D::release()
{
	m_sup.release();
	m_blinkSup.release();
	m_rotateSup.release();
	m_HPBar.release();

	return true;
}

bool MyPlayer2D::boundaryCheck()
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
		m_vVelocity.y = 0.0f;
	}
	if (m_SPRect.pos.y > m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		ret = false;
		m_SPRect.pos.y = m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f - 0.0001f;
		m_vVelocity.y = 0.0f;
		if (m_aState & MYPS_JUMP) { m_aState &= ~MYPS_JUMP; m_iExtraJumpNum = MAX_EXTRA_JUMP_COUNT; }
	}

	adjustCRect(m_SPRect);

	return ret;
}

void MyPlayer2D::setRotateSpeed(FLOAT fRSpeed)
{
	m_fRotateAnglePerSec = fRSpeed;
}

void MyPlayer2D::playShotSound()
{
	m_pShotSound->playEffect();
	m_pShotSound->volumeDown(80);
}

void MyPlayer2D::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MYRND_FRANGE(0.0f, 1.0f);

	if (m_weaponType == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			MyEffect* newE = new MyProjectile;
			*newE = *pEffectPreset;
			newE->m_SPRect.pos = m_sup.m_SPRect.pos;
			newE->m_SPRect.fWH.x += m_iAttackGrade;
			newE->m_SPRect.fWH.y += m_iAttackGrade;

			MyVector2F supD = m_sup.getDirection();
			MyVector2F direction = supD;
			if (supD.x < 0.0f) { direction.x += MYRND.getF(-1.0f, -0.1f); }
			else { direction.x += MYRND.getF(0.1f, 1.0f); }
			if (supD.y < 0.0f) { direction.y += MYRND.getF(-1.0f, -0.1f); }
			else { direction.y += MYRND.getF(0.1f, 1.0f); }
			direction.normalization();

			newE->setDirectionAndSpeed(direction, pEffectPreset->m_fSpeed, 0.0f);
			newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };
			newE->m_iDamage = m_iDamage + pEffectPreset->m_iDamage + m_iAttackGrade * 3;

			newE->m_eIdx = m_weaponType;

			effectList.push_back(newE);
		}

		MyEffect* newE = new MyProjectile;
		*newE = *pEffectPreset;
		newE->m_SPRect.pos = m_sup.m_SPRect.pos;
		newE->m_SPRect.fWH.x += m_iAttackGrade;
		newE->m_SPRect.fWH.y += m_iAttackGrade;
		newE->setDirectionAndSpeed(m_sup.getDirection(), pEffectPreset->m_fSpeed, 0.0f);
		newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };
		newE->m_iDamage = m_iDamage + pEffectPreset->m_iDamage + m_iAttackGrade * 8;
		newE->m_eIdx = m_weaponType;

		effectList.push_back(newE);
	}
	else
	{
		MyEffect* newE = new MyProjectile;
		*newE = *pEffectPreset;
		newE->m_SPRect.pos = m_sup.m_SPRect.pos;
		newE->m_SPRect.fWH.x += m_iAttackGrade;
		newE->m_SPRect.fWH.y += m_iAttackGrade;
		newE->setDirectionAndSpeed(m_sup.getDirection(), pEffectPreset->m_fSpeed, 0.0f);
		newE->m_color = { MYRND.getF(), MYRND.getF(), MYRND.getF(), 1.0f };
		newE->m_iDamage = m_iDamage + pEffectPreset->m_iDamage + m_iAttackGrade;
		newE->m_eIdx = m_weaponType;

		effectList.push_back(newE);
	}
}

FLOAT MyPlayer2D::seq(int k)
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

MyVector2F MyPlayer2D::staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect)
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
			m_SPRect.pos.y = CObjRect.pos.y - m_SPRect.fWH.v[1] * 0.5f - 0.0001f;
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

MyVector2F MyPlayer2D::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& cRect)
{
	if (!m_bHitFlag)
	{
		m_iCurHitPoint -= pCObj->m_iDamage;

		m_fHitTimer = 0.0f;
		m_bHitFlag = true;
		m_bInputNullifyFlag = true;

		setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultcollisionshader.txt");

		if (cRect.pos.x < m_SPRect.pos.x) { m_vVelocity.x += 1000.0f; }
		else { m_vVelocity.x -= 1000.0f; }

		if (cRect.pos.y + cRect.fWH.y < m_SPRect.pos.y) { m_vVelocity.y += 1.0f; }
		else { m_vVelocity.y -= 1.0f; }

		m_pHitSound->playEffect();
	}

	if (m_iCurHitPoint < 0) { m_bInputNullifyFlag = TRUE; }

	return MyVector2F();
}

MyVector2F MyPlayer2D::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect)
{
	if (!m_bHitFlag)
	{
		m_iCurHitPoint -= pCObj->m_iDamage;

		m_fHitTimer = 0.0f;
		m_bHitFlag = true;
		m_bInputNullifyFlag = true;

		setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultcollisionshader.txt");

		if (cRect.pos.x < m_SPRect.pos.x) { m_vVelocity.x += 1000.0f; }
		else { m_vVelocity.x -= 1000.0f; }

		if (cRect.pos.y + cRect.fWH.y < m_SPRect.pos.y) { m_vVelocity.y += 1.0f; }
		else { m_vVelocity.y -= 1.0f; }

		m_pHitSound->volumeDown(80);
		m_pHitSound->playEffect();
	}

	if (m_iCurHitPoint < 0) { m_bInputNullifyFlag = TRUE; }

	return MyVector2F();
}
