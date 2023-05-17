#pragma once
#include "myobject2d.h"
#include "mycollision.h"

#define MAX_EXTRA_JUMP_COUNT 1

enum MyDirectionState	{ MYPS_LEFT, MYPS_RIGHT };
enum MyActionState 
{
	MYPS_IDLE = 0,
	MYPS_WALK = 1,
	MYPS_JUMP = 2,
	MYPS_RUN = 4,
	MYPS_DASH = 8
};

class MyMovementTestDummy : public MyObject2D
{
protected:
	UINT			m_aState;
	BOOL			m_moveFlag;
	BOOL			m_upFlag;
	INT				m_iExtraJumpNum;
	MyExRect		m_prevCSRect;
	FLOAT			m_fJumpPower;
	FLOAT			m_fElapseJumpTime;
	FLOAT			m_fBlinkDist;
	FLOAT			m_fBlinkTimer;
	FLOAT			m_fRotateAnglePerSec;
	FLOAT			m_fCurRotateAngle;

	MySound*		m_pShotSound;

public:
	MyObject2D*		m_pSup;
	MyObject2D*		m_pBlinkSup;
	MyObject2D*		m_pRotateSup;

	MyMovementTestDummy();
	virtual ~MyMovementTestDummy();

	bool init() override;
	bool frame() override;
	bool postFrame(const MyExRect& camRt, FLOAT radian = 0.0f) override;
	bool render() override;
	bool release() override;

	bool boundaryCheck() override;

	void setRotateSpeed(FLOAT fRSpeed);
	void playShotSound();

	void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList,
		MyObject2D* pTarget) override;

	FLOAT seq(int k);

	//정적지형 오브젝트와의 충돌 처리를 하기위한 핸들러
	MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect) override;

	////동적 오브젝트와의 충돌 처리를 하기위한 핸들러
	//MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect);
};