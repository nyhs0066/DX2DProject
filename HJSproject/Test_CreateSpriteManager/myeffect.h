#pragma once
#include "mysprite.h"
#include "myobject2d.h"

class MyEffect : public MyObject2D
{
public:
	MySingleTextureSprite*	m_pSprite;

	FLOAT		m_fLifeSpanT;
	FLOAT		m_fElapseT;
	FLOAT		m_fplayT;
	FLOAT		m_fStepT;

	FLOAT		m_fTimer;
	UINT		m_iCuridx;

	MyEffect();
	~MyEffect();

	bool loadSprite(wstring wszSpriteName);

	bool init() override;	//�⺻ �ʱⰪ�� �ο��Ѵ�.
	bool frame() override;	//�� �������� ��ü�� ���� ���θ� ��ȯ�Ѵ�.
};