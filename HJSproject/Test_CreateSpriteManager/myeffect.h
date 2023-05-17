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

	bool init() override;	//기본 초기값을 부여한다.
	bool frame() override;	//이 프레임은 객체의 유지 여부를 반환한다.
};