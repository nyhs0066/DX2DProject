#pragma once
#include "myobject2d.h"
#include "myspacepartition.h"

enum ENEMY_STATE {	ES_IDLE = 0, 
					ES_TRACK = 1,
					ES_ATTACK = 2 };

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