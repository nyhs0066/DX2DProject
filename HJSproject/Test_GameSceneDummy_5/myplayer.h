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

class MyPlayer2D : public MyObject2D
{
protected:
	//���� ���� �÷���
	UINT			m_aState;
	BOOL			m_moveFlag;
	BOOL			m_upFlag;

	//���� �Ӽ���
	INT				m_iExtraJumpNum;
	FLOAT			m_fJumpPower;
	FLOAT			m_fElapseJumpTime;
	
	//��ũ �Ӽ���
	FLOAT			m_fBlinkDist;
	FLOAT			m_fBlinkTimer;
	
	//ȸ�� �Ӽ���
	FLOAT			m_fRotateAnglePerSec;
	FLOAT			m_fCurRotateAngle;

	//�ǰ� �Ӽ���
	BOOL			m_bHitFlag;
	FLOAT			m_fHitTimer;
	FLOAT			m_fFlickerTimer;
	UINT			m_iFlickerCount;
	FLOAT			m_fInvincibliltyTime;
	FLOAT			m_fInputNullifyTime;

	//���� �浹 �簢�� ��ġ
	MyExRect		m_prevCSRect;

	//���� �Ӽ���
	MySound*		m_pShotSound;
	MySound*		m_pHitSound;

public:
	BOOL			m_bInputNullifyFlag;

	//���� ��ü
	MyObject2D		m_sup;
	MyObject2D		m_blinkSup;
	MyObject2D		m_rotateSup;

	HPBar			m_HPBar;

	UINT			m_weaponType;
	UINT			m_iAttackGrade;
	UINT			m_iArrackSpeedGrade;
	UINT			m_iHpGen;
	FLOAT			m_fRegenTimer;

	MyPlayer2D();
	virtual ~MyPlayer2D();

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

	//�������� ������Ʈ���� �浹 ó���� �ϱ����� �ڵ鷯
	MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect) override;

	////���� ������Ʈ���� �浹 ó���� �ϱ����� �ڵ鷯
	MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& cRect) override;
	MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& cRect) override;
};