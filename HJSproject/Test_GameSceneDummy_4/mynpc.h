#pragma once
#include "myobject2d.h"
#include "myspacepartition.h"

enum ENEMY_STATE {	ES_IDLE = 0, 
					ES_TRACK = 1,
					ES_ATTACK = 2,
					ES_EVADE = 4};

enum BOSS_STATE { BS_IDLE, BS_DIRECT_ATTACK, BS_SPAWN, BS_AIR_ATTACK, BS_DEFENCE };

class MyNpc2D : public MyObject2D
{
public:
	FLOAT m_fHitTimer;
	BOOL m_bLifeFlag;

	MyNpc2D();
	virtual ~MyNpc2D();
};

class MyEnemy : public MyNpc2D
{
protected:
	MyObject2D* m_pTarget;
	HPBar		m_HPbar;

public:
	UINT		m_iEnemyId;
	UINT		m_state;

	MyEnemy();
	virtual ~MyEnemy();

	bool init() override;
	bool frame() override;
	bool postFrame(const MyExRect& camRt, FLOAT radian = 0.0f);
	bool render() override;
	bool release() override;

	virtual bool setTarget(MyObject2D* pTarget);
	
	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;
};

class MyHitDummy : public MyNpc2D
{
public:
	MyHitDummy();
	~MyHitDummy();

	bool frame() override;

	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;
};

class E_Seeker : public MyEnemy
{
private:
	FLOAT m_fEvadeTimer;

public:
	E_Seeker();
	~E_Seeker();

	bool init() override;
	bool frame() override;

	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;
};

class E_Shooter : public MyEnemy
{
private:
	vector<MyObject2D*> m_tempList;
	MyExRect m_prevCSRect;

public:
	bool m_bLandingFlag;
	bool m_bTimerFlag;
	FLOAT timer;

	E_Shooter();
	~E_Shooter();

	bool init() override;
	bool frame() override;

	MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;

	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, 
		MyObject2D* pTarget) override;
	bool boundaryCheck() override;
};

class E_bounder : public MyEnemy
{
private:
	vector<MyObject2D*> m_tempList;
	UINT m_iBoundCount;
	UINT m_iCollisionPlane;	//0 : 왼쪽 | 1 : 오른쪽 | 2 : 위쪽 | 3 : 아래쪽
	MyExRect m_prevCSRect;

public:
	E_bounder();
	~E_bounder();

	bool init() override;
	bool frame() override;

	MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;
	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList,
		MyObject2D* pTarget) override;

	bool boundaryCheck() override;
};

class BossHelper_AIR
{
public:
	MyExRect m_SPRect;
	FLOAT m_fTimeLimit;
	FLOAT m_fTimer;
	FLOAT m_fProjSpeed;
	INT m_iDamage;

	BOOL m_bActiveFlag;
	BOOL readyFlag;

	MyVector2F m_vDirection;

	bool frame();

	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList,
		MyObject2D* pTarget);
};

class BossHelper_DEF
{
public:
	vector<vector<MyVector2F>> vD;

	MyExRect m_SPRect;
	BOOL m_bActiveFlag;
	FLOAT m_fTimeLimit;
	FLOAT m_fTimer;
	FLOAT m_fProjSpeed;
	FLOAT m_fProjSize;
	INT m_iDamage;

	BOOL readyFlag;

	bool frame();

	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList,
		int idx);
};

//enum BOSS_STATE { BS_IDLE, BS_DIRECT_ATTACK, BS_SPAWN, BS_AIR_ATTACK, BS_DEFENCE };
class MyFirstBoss : public MyEnemy
{
public:
	BOSS_STATE m_bState;
	MyObject2D* pTarget;

	MyHitDummy m_shield;

	FLOAT m_fNormalProjSpeed;
	FLOAT m_fDirectAttackProjSpeed;
	FLOAT m_fDefenceProjSpeed;

	FLOAT m_fStateTransitionTime;
	FLOAT m_fSTTimer;

	FLOAT m_fDefenseTime;
	FLOAT m_fDefenseTimer;

	BossHelper_AIR m_airHelper[6];
	BossHelper_DEF m_defHelper[3];

	BOOL m_bSpawnFlag;
	BOOL m_bDAFlag;

	MyFirstBoss();
	~MyFirstBoss();

	bool init() override;
	bool frame() override;
	bool postFrame(const MyExRect& camRt, FLOAT radian = 0.0f) override;
	bool render() override;
	bool release() override;

	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt) override;
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt) override;
	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList,
		MyObject2D* pTarget) override;
};

