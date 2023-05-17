#pragma once
#include "myspritemanager.h"
#include "myobject2d.h"

class MyEffectPreset
{
public:
	MyObject2D* m_pDrawing;
	MySingleTextureSprite* m_pSprite;

	MyEffectPreset();
	~MyEffectPreset();

	bool create(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName);
	bool create(wstring wszShaderName, wstring wszTexName,
		wstring wszMaskName,wstring wszSpriteName);
};

class MyEffect
{
public:
	//채워야 하는 것
	MyEffectPreset* m_pEPreset;

	FLOAT		m_fLifeSpanT;
	FLOAT		m_fplayT;

	MyRect m_SPRect;
	FLOAT m_fSpeed;
	MyVector2F m_direction;
	MyVector4F m_color;

	//자동으로 채워지는 것
	FLOAT		m_fStepT;
	FLOAT		m_fElapseT;
	FLOAT		m_fTimer;
	UINT		m_iCuridx;
	
	MyRect m_TRect;
	MyRect m_CSRect;

	MyEffect();
	~MyEffect();

	virtual bool update();
	virtual void setPosRect(MyRect posRt);
	virtual void setTimeProperty(FLOAT fLifeSpanT, FLOAT fPlayT);
	virtual bool preRender(const MyRect& camRt);
};

class MyProjectile : public MyEffect
{
public:
	MyEffectPreset* m_pCreateEffectPreset;
	MyEffectPreset* m_pDestructEffectPreset;

	INT m_iDamage;

	bool update() override;
	bool setProjectileProperty(MyEffectPreset* pPreset, MyRect posRt, FLOAT fLifeSpanT, FLOAT fPlayT, MyVector2F vDirection, FLOAT fspeed, UINT iDmg);
};