#pragma once
#include "myobject2d.h"
#include "mycollision.h"

#define MAX_JUMP_COUNT 2

enum MyDirectionState	{ MYPS_LEFT, MYPS_RIGHT };
enum MyActionState 
{
	MYPS_IDLE = 0,
	MYPS_WALK = 1,
	MYPS_JUMP = 2,
	MYPS_RUN = 4,
	MYPS_DASH = 8
};

class MyPlayer2D : public MyObject2D
{
protected:
	UINT m_dState;		//direction state
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
	UINT			m_aState;
	BOOL			m_moveFlag;
	BOOL			m_upFlag;
	INT				m_iEnableJumpNum;
	MyRect			m_prevCSRect;
	FLOAT			m_fJumpPower;
	FLOAT			m_fElapseJumpTime;

public:
	MyObject2D		m_sup;

	MyMovementTestDummy();
	virtual ~MyMovementTestDummy();

	bool init() override;
	bool frame() override;
	bool postFrame(const MyRect& camRt) override;
	bool render() override;

	bool boundaryCheck() override;

	FLOAT seq(int k);

	//�������� ������Ʈ���� �浹 ó���� �ϱ����� �ڵ鷯
	MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyRect& cRect) override;

	////���� ������Ʈ���� �浹 ó���� �ϱ����� �ڵ鷯
	//MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyRect& cRect);
};