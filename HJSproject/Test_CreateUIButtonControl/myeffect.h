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

	bool createEffectPreset(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName);
	bool createEffectPreset(wstring wszShaderName, wstring wszTexName,
		wstring wszMaskName,wstring wszSpriteName);
};

class MyEffect
{
public:
	MyEffectPreset* m_pEPreset;

	FLOAT		m_fLifeSpanT;
	FLOAT		m_fplayT;
	FLOAT		m_fStepT;

	FLOAT		m_fElapseT;
	FLOAT		m_fTimer;
	UINT		m_iCuridx;

	MyRect m_SPRect;
	MyRect m_TRect;
	MyRect m_CSRect;

	MyEffect();
	~MyEffect();

	virtual bool init();
	virtual bool update();
	virtual void setPosition(MyVector2F pos);
	virtual void setTimeProperty(FLOAT fLifeSpanT, FLOAT fPlayT);
	virtual bool preRender(const MyRect& camRt);
};