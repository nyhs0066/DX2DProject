#include "mynpc.h"

MyNpc2D::MyNpc2D()
{
}

MyNpc2D::~MyNpc2D()
{
	release();
}

MyEnemy::MyEnemy()
{
	m_state = ES_IDLE;
	m_iEnemyId = 0;
	m_fHitTimer = 0.0f;
	m_bLifeFlag = TRUE;
	m_pTarget = nullptr;
}

MyEnemy::~MyEnemy()
{
	release();
}

bool MyEnemy::init()
{
	m_HPbar.create(L"../../data/shader/mydefaultshader.txt", this);

	return true;
}

bool MyEnemy::frame()
{
	m_fHitTimer += MAINTIMER.getOneFrameTimeF();

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 1.0f, 1.0f, 1.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");
	}
	return true;
}

bool MyEnemy::postFrame(const MyExRect& camRt, FLOAT radian)
{
	MyObject2D::postFrame(camRt);
	m_HPbar.postFrame(camRt);

	return true;
}

bool MyEnemy::render()
{
	MyObject2D::render();
	m_HPbar.render();
	return false;
}

bool MyEnemy::release()
{
	MyObject2D::release();
	m_pTarget = nullptr;
	m_HPbar.release();

	return false;
}

bool MyEnemy::setTarget(MyObject2D* pTarget)
{
	this->m_pTarget = pTarget;

	return true;
}

MyVector2F MyEnemy::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyEnemy::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}



MyHitDummy::MyHitDummy()
{
	m_vColor = { 1.0f, 0.0f, 1.0f, 0.5f };
	reverseFlag = FALSE;
}

MyHitDummy::~MyHitDummy()
{
	release();
}

bool MyHitDummy::frame()
{
	FLOAT deltaT = MAINTIMER.getOneFrameTimeF();

	m_fHitTimer += deltaT;

	if (m_fHitTimer > FIXFRAMET)
	{
		if (reverseFlag) 
		{
			m_vColor.v[0] -= deltaT * 0.5f;
			m_vColor.v[2] -= deltaT * 0.5f;
		}
		else
		{
			m_vColor.v[0] += deltaT * 0.5f;
			m_vColor.v[2] += deltaT * 0.5f;
		}

		if (m_vColor.v[0] > 1.0f) 
		{ 
			m_vColor.v[0] = 1.0f;
			reverseFlag = !reverseFlag; 
		}
		else if (m_vColor.v[0] < 0.0f)
		{
			m_vColor.v[0] = 0.0f;
			reverseFlag = !reverseFlag;
		}

		setColors(m_vColor);
		setShader(L"../../data/shader/mydefaultshader.txt");
	}
	return true;
}

MyVector2F MyHitDummy::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyHitDummy::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}

E_Seeker::E_Seeker()
{
	m_iEnemyId = 1;
	m_state = ES_TRACK;

	S_seeker_flee = LOAD_SOUND(L"../../data/sound/seeker_flee.wav");
}

E_Seeker::~E_Seeker()
{
	release();
}

bool E_Seeker::init()
{
	m_iMaxHitPoint = 100;
	m_iCurHitPoint = m_iMaxHitPoint;
	m_iDamage = 12;

	m_fSpeed = 300.0f;
	setColors({ 0.5f, 0.0f, 1.0f, 1.0f });

	m_fEvadeTimer = 0.0f;
	m_state = ES_TRACK;

	MyEnemy::init();

	return true;
}

bool E_Seeker::frame()
{
	FLOAT dT = MAINTIMER.getOneFrameTimeF();

	if (m_state & ES_EVADE)
	{
		m_fEvadeTimer += dT;

		if (m_fEvadeTimer > 2.0f) 
		{ 
			m_fEvadeTimer = 0.0f;
			m_state &= ~ES_EVADE;
			m_state |= ES_TRACK; 
		}

		m_SPRect.pos += m_vDirection * m_fSpeed * 2.0f * dT;
	}
	else
	{
		MyVector2F vDirection = m_pTarget->m_SPRect.pos - m_SPRect.pos;

		if (vDirection.length() < 10.0f) 
		{ 
			m_state |= ES_EVADE;
			m_state &= ~ES_TRACK;
			vDirection = -vDirection;
			vDirection.normalization();
			S_seeker_flee->playEffect();
		}
		else { vDirection.normalization(); }
		
		m_vDirection = vDirection;

		m_SPRect.pos += m_vDirection * m_fSpeed * dT;
	}

	m_fHitTimer += dT;

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 0.5f, 0.0f, 1.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");
	}

	return true;
}

MyVector2F E_Seeker::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	if (!(m_state & ES_EVADE))
	{
		m_state |= ES_EVADE;
		m_vDirection = -m_vDirection;

		S_seeker_flee->playEffect();
	}

	return MyVector2F();
}

MyVector2F E_Seeker::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}

E_Shooter::E_Shooter()
{
	m_iEnemyId = 2;
	m_bLandingFlag = false;
	m_bTimerFlag = false;

	S_shooter_shot = LOAD_SOUND(L"../../data/sound/shooter_shot.wav");

	timer = 0.0f;
}

E_Shooter::~E_Shooter()
{
	release();
}

bool E_Shooter::init()
{
	MYRND_IRANGE(0, 1);
	if (MYRND.getI()) { m_vDirection = { 1.0f, 0.0f }; }
	else { m_vDirection = { -1.0f, 0.0f }; }

	m_fMass = 1.0f;
	timer = 0.0f;
	m_iDamage = 25;
	
	m_iMaxHitPoint = 150;
	m_iCurHitPoint = m_iMaxHitPoint;

	m_fSpeed = 100.0f;
	setColors({ 0.5f, 0.5f, 0.0f, 1.0f });

	MyVector2F gravity = { 0.0f, 1000.0f };
	setForce(gravity);

	MyEnemy::init();

	return true;
}

bool E_Shooter::frame()
{
	FLOAT dT = MAINTIMER.getOneFrameTimeF();

	m_fHitTimer += dT;

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 0.5f, 0.5f, 0.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");
	}

	if (m_bLandingFlag)
	{
		if (MyVector2F::getDistance(m_pTarget->m_SPRect.pos, m_SPRect.pos) <= 750.0f)
		{
			MYRND_IRANGE(0, 2000);
			if (MYRND.getI() == 4) { m_state = ES_TRACK; }
		}
	}

	if (m_state & ES_TRACK)
	{
		timer += dT;

		if (timer > 1.0f) 
		{ 
			m_state = ES_ATTACK;
			m_bTimerFlag = false;
			timer = 0.0f;
			m_state &= ~ES_TRACK;
		}
	}
	else
	{
		m_prevCSRect = m_CSRect;

		m_SPRect.pos += m_vDirection * m_fSpeed * dT;

		m_vAcceleration = m_vForce * (1.0f / m_fMass);
		m_SPRect.pos += m_vVelocity * dT + m_vAcceleration * dT * dT * 0.5f;
		m_vVelocity += m_vAcceleration * dT;

		adjustCRect(m_SPRect);

		m_tempList.clear();

		MYSPACE.getStaticCollisionList(this, m_tempList);

		for (auto it : m_tempList)
		{
			staticCollisionHandler(it, MyCollision::getIntersection2F(m_CSRect, it->getCSRect()));
		}

		boundaryCheck();
	}

	return true;
}

MyVector2F E_Shooter::staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	MyExRect temp = m_prevCSRect;
	MyExRect CObjRect = pCObj->getCSRect();
	temp.pos.x = m_CSRect.pos.x;

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.x - m_prevCSRect.pos.x > 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x - m_SPRect.fWH.v[0] * 0.5f - 0.001f;
			m_vDirection.x = -m_vDirection.x;
		}
		else if (m_CSRect.pos.x - m_prevCSRect.pos.x < 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x + CObjRect.fWH.v[0] + m_SPRect.fWH.v[0] * 0.5f + 0.001f;
			m_vDirection.x = -m_vDirection.x;
		}
	}

	temp = m_prevCSRect;
	temp.pos.y = m_CSRect.pos.y;


	if (MyCollision::rectToRect(temp, CObjRect))
	{
		m_SPRect.pos.y = CObjRect.pos.y - m_SPRect.fWH.v[1] * 0.5f - 0.0003f;
		m_vVelocity.y = 0.0f;

		if (!m_bLandingFlag) 
		{ 
			m_bLandingFlag = true; 
			m_BRect.pos.x = pCObj->getCSRect().pos.x - m_CSRect.fWH.x * 0.5f;
			m_BRect.fWH.x = pCObj->getCSRect().pos.x + pCObj->getCSRect().fWH.x + m_CSRect.fWH.x * 0.5f;
		}
	}

	adjustCRect(m_SPRect);

	return CObjRect.pos + CObjRect.fWH * 0.5f;
}

MyVector2F E_Shooter::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F E_Shooter::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}

void E_Shooter::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MyVector2F vDirection = pTarget->m_SPRect.pos - m_SPRect.pos;
	vDirection.normalization();

	for (int i = 0; i < 2; i++)
	{
		MyEffect* newE = new MyProjectile;
		*newE = *pEffectPreset;
		MyVector2F supD = vDirection;
		MyVector2F direction = supD;
		if (supD.x < 0.0f) { direction.x += MYRND.getF(-1.0f, -0.1f); }
		else { direction.x += MYRND.getF(0.1f, 1.0f); }
		if (supD.y < 0.0f) { direction.y += MYRND.getF(-1.0f, -0.1f); }
		else { direction.y += MYRND.getF(0.1f, 1.0f); }
		direction.normalization();

		newE->m_SPRect.pos = m_SPRect.pos + direction * 40.0f;
		newE->m_SPRect.fWH = { 20.0f, 20.0f };
		newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
		newE->setDirectionAndSpeed(direction, 400.0f, 0.0f);
		newE->m_iDamage = m_iDamage;

		effectList.push_back(newE);
	}

	MyEffect* newE = new MyProjectile;
	*newE = *pEffectPreset;
	newE->m_SPRect.pos = m_SPRect.pos + vDirection * 40.0f;
	newE->m_SPRect.fWH = { 20.0f, 20.0f };
	newE->setDirectionAndSpeed(vDirection, 400.0f, 0.0f);
	newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	newE->m_iDamage = m_iDamage;
	effectList.push_back(newE);

	S_shooter_shot->playEffect();
	S_shooter_shot->volumeDown(40);
}

bool E_Shooter::boundaryCheck()
{
	if (m_SPRect.pos.x < m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f)
	{
		m_SPRect.pos.x = m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f;
		m_vDirection.x = -m_vDirection.x;
	}
	if (m_SPRect.pos.x > m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f)
	{
		m_SPRect.pos.x = m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f;
		m_vDirection.x = -m_vDirection.x;
	}
	if (m_SPRect.pos.y > m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		m_SPRect.pos.y = m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f - 0.0001f;
		m_vVelocity.y = 0.0f;

		if (!m_bLandingFlag) { m_bLandingFlag = true; }
	}

	adjustCRect(m_SPRect);

	return true;
}

E_bounder::E_bounder()
{
	m_iEnemyId = 3;
	m_state = ES_IDLE;

	m_vDirection = { MYRND.getF(-1.0, 1.0), MYRND.getF(-1.0, 1.0) };
	m_vDirection.normalization();

	S_bounder_bounding = LOAD_SOUND(L"../../data/sound/bounder_bounding.wav");
}

E_bounder::~E_bounder()
{
	release();
}

bool E_bounder::init()
{
	setColors({ 0.0f, 0.5f, 1.0f, 1.0f });
	m_iDamage = 25;
	m_fHitTimer = 0.0f;
	m_fSpeed = 200.0f;
	m_iBoundCount = 0;

	m_iMaxHitPoint = 250;
	m_iCurHitPoint = m_iMaxHitPoint;

	MyEnemy::init();

	return true;
}

bool E_bounder::frame()
{
	m_prevCSRect = m_CSRect;

	m_SPRect.pos += m_vDirection * m_fSpeed * MAINTIMER.getOneFrameTimeF();
	adjustCRect(m_SPRect);

	m_fHitTimer += MAINTIMER.getOneFrameTimeF();

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 0.0f, 0.5f, 1.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");
	}

	m_tempList.clear();

	MYSPACE.getStaticCollisionList(this, m_tempList);

	for (auto it : m_tempList)
	{
		staticCollisionHandler(it, MyCollision::getIntersection2F(m_CSRect, it->getCSRect()));
	}

	boundaryCheck();

	if (m_iBoundCount > 10)
	{
		MyVector2F vDirection = m_pTarget->m_SPRect.pos - m_SPRect.pos;
		vDirection.normalization();
		m_vDirection = vDirection;

		m_iBoundCount -= 10;
	}

	return true;
}

MyVector2F E_bounder::staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	MyExRect temp = m_prevCSRect;
	MyExRect CObjRect = pCObj->getCSRect();
	temp.pos.x = m_CSRect.pos.x;

	if (MyCollision::rectToRect(temp, CObjRect))
	{
		if (m_CSRect.pos.x - m_prevCSRect.pos.x > 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x - m_SPRect.fWH.v[0] * 0.5f - 0.001f;
			m_vDirection.x = -m_vDirection.x;
			m_iBoundCount++;
			m_state |= ES_ATTACK;
		}
		else if (m_CSRect.pos.x - m_prevCSRect.pos.x < 0.0f)
		{
			m_SPRect.pos.x = CObjRect.pos.x + CObjRect.fWH.v[0] + m_SPRect.fWH.v[0] * 0.5f + 0.001f;
			m_vDirection.x = -m_vDirection.x;
			m_iBoundCount++;
			m_state |= ES_ATTACK;
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
			m_vDirection.y = -m_vDirection.y;
			m_iBoundCount++;
			m_state |= ES_ATTACK;
		}
		else if (m_CSRect.pos.y - m_prevCSRect.pos.y < 0.0f)
		{
			m_SPRect.pos.y = CObjRect.pos.y + CObjRect.fWH.v[1] + m_SPRect.fWH.v[0] * 0.5f + 0.001f;
			m_vVelocity.y = 0.0f;
			m_vDirection.y = -m_vDirection.y;
			m_iBoundCount++;
			m_state |= ES_ATTACK;
		}
	}

	adjustCRect(m_SPRect);

	S_bounder_bounding->playEffect();

	return CObjRect.pos + CObjRect.fWH * 0.5f;
}

MyVector2F E_bounder::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F E_bounder::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	return MyVector2F();
}

void E_bounder::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MyVector2F vDirection[3];
	MYRND_FRANGE(-1.0f, 1.0f);

	switch (m_iCollisionPlane)
	{
	case 0 :
		vDirection[0] = { 1.0f, MYRND.getF() };
		vDirection[1] = { 1.0f, 0.0f };
		vDirection[2] = { 1.0f, MYRND.getF() };
		break;
	case 1:
		vDirection[0] = { -1.0f, MYRND.getF() };
		vDirection[1] = { -1.0f, 0.0f };
		vDirection[2] = { -1.0f, MYRND.getF() };
		break;
	case 2:
		vDirection[0] = { MYRND.getF(), 1.0f  };
		vDirection[1] = { 0.0f, 1.0f };
		vDirection[2] = { MYRND.getF(), 1.0f };
		break;
	case 3:
		vDirection[0] = { MYRND.getF(), -1.0f };
		vDirection[1] = { 0.0f, -1.0f };
		vDirection[2] = { MYRND.getF(), -1.0f };
		break;
	}

	for (auto it : vDirection) 
	{ 
		it.normalization(); 

		MyEffect* newE = new MyProjectile;
		*newE = *pEffectPreset;
		newE->m_SPRect.pos = m_SPRect.pos + it * 75.0f;
		newE->m_SPRect.fWH = { 30.0f, 30.0f };
		newE->setDirectionAndSpeed(it, 100.0f, 0.0f);
		newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
		newE->m_iDamage = m_iDamage;
		newE->m_fLifeSpanT = 10.0f;
		effectList.push_back(newE);
	}
}

bool E_bounder::boundaryCheck()
{
	bool check = false;

	//왼쪽 충돌
	if (m_SPRect.pos.x < m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f)
	{
		m_SPRect.pos.x = m_BRect.pos.x + m_SPRect.fWH.v[0] * 0.5f + 0.1f;
		m_vDirection.x = -m_vDirection.x;
		m_state |= ES_ATTACK;
		m_iBoundCount++;
		m_iCollisionPlane = 0;

		check = true;
	}
	//오른쪽 충돌
	if (m_SPRect.pos.x > m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f)
	{
		m_SPRect.pos.x = m_BRect.fWH.v[0] - m_SPRect.fWH.v[0] * 0.5f - 0.1f;
		m_vDirection.x = -m_vDirection.x;
		m_state |= ES_ATTACK;
		m_iBoundCount++;
		m_iCollisionPlane = 1;

		check = true;
	}
	//위쪽 충돌
	if (m_SPRect.pos.y < m_BRect.pos.y + m_SPRect.fWH.v[1] * 0.5f)
	{
		m_SPRect.pos.y = m_BRect.pos.y + m_SPRect.fWH.v[1] * 0.5f + 0.1f;
		m_vDirection.y = -m_vDirection.y;
		m_state |= ES_ATTACK;
		m_iBoundCount++;
		m_iCollisionPlane = 2;

		check = true;
	}
	//아래쪽 충돌
	if (m_SPRect.pos.y > m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f)
	{
		m_SPRect.pos.y = m_BRect.fWH.v[1] - m_SPRect.fWH.v[1] * 0.5f - 0.1f;
		m_vDirection.y = -m_vDirection.y;
		m_state |= ES_ATTACK;
		m_iBoundCount++;
		m_iCollisionPlane = 3;

		check = true;
	}
	if (check) 
	{ 
		S_bounder_bounding->playEffect(); 
		S_bounder_bounding->volumeDown(80);
	}
	
	adjustCRect(m_SPRect);

	return true;
}

MyFirstBoss::MyFirstBoss()
{
	for (int i = 0; i < 6; i++)
	{
		m_airHelper[i].m_SPRect.pos = { 191.6f + 383.3f * i, 200.0f };
		m_airHelper[i].m_fTimeLimit = 3.0f + 0.5f*i;
		m_airHelper[i].m_fTimer = 0.0f;
		m_airHelper[i].m_fProjSpeed = 200.0f;
		m_airHelper[i].m_iDamage = 33;

		m_airHelper[i].m_bActiveFlag = false;
		m_airHelper[i].readyFlag = false;
		m_airHelper[i].m_vDirection = { 0.0f, 1.0f };

		m_airHelper[i].S_boss_air_shot = LOAD_SOUND(L"../../data/sound/boss_air_shot.wav");
	}

	vector<vector<MyVector2F>> vDir;
	vDir.resize(3);

	MyVector2F temp;
	temp = { 1.0f, -1.0f };
	temp.normalization();
	vDir[0].push_back(temp);
	temp = { 1.0f, 1.0f };
	temp.normalization();
	vDir[0].push_back(temp);
	temp = { 1.0f, 0.0f };
	temp.normalization();
	vDir[0].push_back(temp);

	temp = { 1.0f, -1.73f };
	temp.normalization();
	vDir[1].push_back(temp);
	temp = { 1.0f, 1.73f };
	temp.normalization();
	vDir[1].push_back(temp);
	temp = { 1.73f, 1.0f };
	temp.normalization();
	vDir[1].push_back(temp);
	temp = { 1.73f, -1.0f };
	temp.normalization();
	vDir[1].push_back(temp);

	temp = { 1.73f, -1.0f };
	temp.normalization();
	vDir[2].push_back(temp);
	temp = { 1.73f, 1.0f };
	temp.normalization();
	vDir[2].push_back(temp);
	temp = { 1.0f, -1.73f };
	temp.normalization();
	vDir[2].push_back(temp);
	temp = { 1.0f, 1.73f };
	temp.normalization();
	vDir[2].push_back(temp);
	temp = { 1.0f, 0.0f };
	temp.normalization();
	vDir[2].push_back(temp);

	m_defHelper[0].vD = vDir;
	m_defHelper[0].m_bActiveFlag = false;
	m_defHelper[0].m_fTimeLimit = 2.0f;
	m_defHelper[0].m_fTimer = 0.0f;
	m_defHelper[0].m_fProjSpeed = 300.0f;
	m_defHelper[0].m_fProjSize = 125.0f;
	m_defHelper[0].m_iDamage = 25;
	m_defHelper[0].readyFlag = false;
	m_defHelper[0].S_boss_def_shot = LOAD_SOUND(L"../../data/sound/boss_def_first.wav");

	m_defHelper[1].vD = vDir;
	m_defHelper[1].m_bActiveFlag = false;
	m_defHelper[1].m_fTimeLimit = 3.0f;
	m_defHelper[1].m_fTimer = 0.0f;
	m_defHelper[1].m_fProjSpeed = 200.0f;
	m_defHelper[1].m_fProjSize = 150.0f;
	m_defHelper[1].m_iDamage = 30;
	m_defHelper[1].readyFlag = false;
	m_defHelper[1].S_boss_def_shot = LOAD_SOUND(L"../../data/sound/boss_def_second.wav");

	m_defHelper[2].vD = vDir;
	m_defHelper[2].m_bActiveFlag = false;
	m_defHelper[2].m_fTimeLimit = 4.0f;
	m_defHelper[2].m_fTimer = 0.0f;
	m_defHelper[2].m_fProjSpeed = 100.0f;
	m_defHelper[2].m_fProjSize = 175.0f;
	m_defHelper[2].m_iDamage = 35;
	m_defHelper[2].readyFlag = false;
	m_defHelper[2].S_boss_def_shot = LOAD_SOUND(L"../../data/sound/boss_def_third.ogg");

	S_DShot = LOAD_SOUND(L"../../data/sound/boss_direct_shot.wav");

	pTarget = nullptr;
}

MyFirstBoss::~MyFirstBoss()
{
	release();
}

bool MyFirstBoss::init()
{
	m_bState = BS_DEFENCE;

	m_iDamage = 40;
	m_fHitTimer = 0.0f;
	m_fSpeed = 0.0f;
	m_fStateTransitionTime = 7.5f;
	m_fSTTimer = 0.0f;

	m_fDefenseTime = 10.0f;
	m_fDefenseTimer = 0.0f;

	m_fDirectAttackTimer = 0.0f;

	m_iMaxHitPoint = 2000;
	m_iCurHitPoint = m_iMaxHitPoint;

	m_fNormalProjSpeed = 300.0f;
	m_fDirectAttackProjSpeed = 1000.0f;
	m_fDefenceProjSpeed = 200.0f;

	m_defHelper[0].m_SPRect = m_SPRect;
	m_defHelper[1].m_SPRect = m_SPRect;
	m_defHelper[2].m_SPRect = m_SPRect;

	m_bSpawnFlag = false;

	m_shield.create(L"../../data/shader/mydefaultShader.txt",
		L"../../data/shapes/HollowSquare.png");
	MyExRect pRect = m_SPRect;
	pRect.fWH = { 500.0f, 500.0f };
	m_shield.m_bLifeFlag = true;
	m_shield.setPosRect(pRect);
	m_shield.adjustCRect(pRect);
	m_shield.m_iMaxHitPoint = 200.0f;
	m_shield.m_iCurHitPoint = 200.0f;

	MyEnemy::init();

	return true;
}

bool MyFirstBoss::frame()
{
	FLOAT deltaT = MAINTIMER.getOneFrameTimeF();

	if (m_shield.m_bLifeFlag)
	{
		m_shield.frame();
	}

	if (m_bState != BS_DEFENCE) { m_fDefenseTimer += deltaT; }

	if ((m_bState & BS_DEFENCE) && !m_shield.m_bLifeFlag)
	{
		m_bState = BS_DIRECT_ATTACK;
		m_fDefenseTimer = 0.0f;
	}

	if (m_fDefenseTimer > m_fDefenseTime)
	{
		m_bState = BS_DEFENCE;
		m_fDefenseTimer = 0.0f;
		m_shield.m_bLifeFlag = TRUE;
		m_shield.m_iCurHitPoint = m_shield.m_iMaxHitPoint;
	}

	m_fHitTimer += deltaT;

	if (m_fHitTimer > FIXFRAMET)
	{
		setColors({ 1.0f, 1.0f, 1.0f, 1.0f });
		setShader(L"../../data/shader/mydefaultshader.txt");
	}

	m_fSTTimer += deltaT;

	for (int i = 0; i < 6; i++) { m_airHelper[i].frame(); }
	for (int i = 0; i < 3; i++) { m_defHelper[i].frame(); }

	if (m_fSTTimer > m_fStateTransitionTime)
	{
		m_fSTTimer -= m_fStateTransitionTime;

		if (m_bState == BS_DEFENCE)
		{
			if (m_SPRect.pos.x < 1200.0f)
			{
				if (!m_defHelper[0].m_bActiveFlag) { m_defHelper[0].m_bActiveFlag = true; }
				if (!m_defHelper[1].m_bActiveFlag) { m_defHelper[1].m_bActiveFlag = true; }
				if (!m_defHelper[2].m_bActiveFlag) { m_defHelper[2].m_bActiveFlag = true; }
			}
		}
		else
		{
			switch (MYRND.getI(0, 3))
			{
			case 0: m_bState = BS_IDLE; break;
			case 1: m_bState = BS_DIRECT_ATTACK; break;
			case 2: m_bState = BS_SPAWN; break;
			case 3: m_bState = BS_AIR_ATTACK; break;
			}
		}
	}

	if (m_bState == BS_AIR_ATTACK)
	{
		for (int i = 0; i < 2; i++)
		{
			m_airHelper[MYRND.getI(0, 5)].m_bActiveFlag = true;
		}

		m_bState = BS_IDLE;
	}

	if (m_bState == BS_DIRECT_ATTACK) 
	{ 
 		m_fDirectAttackTimer += deltaT;

		if (m_fDirectAttackTimer > 1.0f)
		{
			m_bDAFlag = TRUE;
			m_fDirectAttackTimer -= 1.0f;
		}
	}

	if (m_bState == BS_SPAWN) { m_bSpawnFlag = TRUE; }

	return true;
}

bool MyFirstBoss::postFrame(const MyExRect& camRt, FLOAT radian)
{
	if (m_shield.m_bLifeFlag)
	{
		m_shield.postFrame(camRt);
	}
	m_HPbar.postFrame(camRt);

	MyObject2D::postFrame(camRt);
	return false;
}

bool MyFirstBoss::render()
{
	if (m_shield.m_bLifeFlag)
	{
		m_shield.render();
	}
	MyObject2D::render();

	m_HPbar.render();
	return false;
}

bool MyFirstBoss::release()
{
	m_shield.release();
	MyObject2D::release();
	return false;
}

MyVector2F MyFirstBoss::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyFirstBoss::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	m_iCurHitPoint -= pCObj->m_iDamage;

	if (m_iCurHitPoint < 0) { m_bLifeFlag = FALSE; }

	m_fHitTimer = 0.0f;
	setColors({ 1.0f, (FLOAT)m_iCurHitPoint / m_iMaxHitPoint , 0.0f, 1.0f });
	setShader(L"../../data/shader/mydefaultcollisionshader.txt");

	m_fDefenseTimer = 0.0f;

	return MyVector2F();
}

void MyFirstBoss::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MyEffect* newE = new MyProjectile;
	*newE = *pEffectPreset;

	MyVector2F vDir = pTarget->m_SPRect.pos - m_SPRect.pos;
	vDir.normalization();
	newE->m_SPRect.pos = m_SPRect.pos;
	newE->m_SPRect.fWH = { 100.0f, 100.0f };
	newE->setDirectionAndSpeed(vDir, 1000.0f, 0.0f);
	newE->setTimeProperty(3.0f, 1.0f);
	newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	newE->m_iDamage = m_iDamage;
	effectList.push_back(newE);

	S_DShot->playEffect();
}

bool BossHelper_AIR::frame()
{
	if (m_bActiveFlag)
	{
		m_fTimer += MAINTIMER.getOneFrameTimeF();

		if (m_fTimer > m_fTimeLimit)
		{
			readyFlag = true;
			m_bActiveFlag = false;
			m_fTimer = 0.0f;
		}
	}
	return true;
}


void BossHelper_AIR::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget)
{
	MyEffect* newE = new MyProjectile;
	*newE = *pEffectPreset;
	newE->m_SPRect.pos.x = m_SPRect.pos.x;
	newE->m_SPRect.pos.y = -192.0f;
	newE->m_SPRect.fWH = { 383.0f, 383.0f };
	newE->setDirectionAndSpeed(m_vDirection, 200.0f, 0.0f);
	newE->setTimeProperty(10.0f, 1.0f);
	newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	newE->m_iDamage = m_iDamage;
	effectList.push_back(newE);

	S_boss_air_shot->playEffect();
}

bool BossHelper_DEF::frame()
{
	if (m_bActiveFlag)
	{
		m_fTimer += MAINTIMER.getOneFrameTimeF();

		if (m_fTimer > m_fTimeLimit)
		{
			readyFlag = true;
			m_bActiveFlag = false;
			m_fTimer = 0.0f;
		}
	}
	return true;
}

void BossHelper_DEF::createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, int idx)
{
	for (int i = 0; i < vD[idx].size(); i++)
	{
		MyEffect* newE = new MyProjectile;
		*newE = *pEffectPreset;
		newE->m_SPRect.pos = m_SPRect.pos;
		newE->m_SPRect.fWH = { m_fProjSize, m_fProjSize };

		if (m_SPRect.pos.x > 1200.0f)
		{
			MyVector2F Direction = { -vD[idx][i].x, vD[idx][i].y };
			newE->setDirectionAndSpeed(Direction, m_fProjSpeed, 0.0f);
		}
		else
		{
			newE->setDirectionAndSpeed(vD[idx][i], m_fProjSpeed, 0.0f);
		}
			
		newE->setTimeProperty(20.0f, 1.0f);
		newE->m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
		newE->m_iDamage = m_iDamage;
		effectList.push_back(newE);
	}

	S_boss_def_shot->playEffect();
}