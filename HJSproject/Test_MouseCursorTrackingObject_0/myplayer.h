#pragma once
#include "myobject2d.h"
#include "mycollision.h"

enum MyDirectionState	{ MYPS_LEFT, MYPS_RIGHT };
enum MyActionState		{ MYPS_IDLE, MYPS_WALK, MYPS_JUMP };

class MyPlayer2D : public MyObject2D
{
protected:
	MyDirectionState m_dState;		//direction state
	MyActionState m_aState;			//action state
	BOOL m_actionFlag;
	BOOL m_upFlag;
	FLOAT m_fJumpPower;
	FLOAT m_iElapseJumpTimeCounter;
	FLOAT m_fStateTimer;
	UINT m_iStateCounter;

public:
	vector<vector<wstring>> m_stateSpriteSet;

	MyPlayer2D();
	virtual ~MyPlayer2D();

	bool init() override;
	bool frame() override;
};

class MyMovementTestDummy : public MyObject2D
{
protected:
	MyActionState m_aState;
	BOOL moveFlag;

public:
	MyMovementTestDummy();
	virtual ~MyMovementTestDummy();

	bool init() override;
	bool frame() override;

	bool boundaryCheck();
	void collisionHandler(const COLLISION_PLANE cPlane, const MyObject2D* pCobj = nullptr);

	void setAerial();
};