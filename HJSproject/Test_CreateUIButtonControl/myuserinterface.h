#pragma once
#include "myobject2d.h"
#include "myspritemanager.h"
#include "mycollision.h"

enum UI_BUTTON_STATE { UB_DISABLE, UB_IDLE, UB_PUSH, UB_SELECT };

class MyUserInterface : public MyObject2D
{
protected:
	MySingleTextureSprite* m_UISTsprite;
	MyMultiTextureSprite* m_UIMTsprite;

public:
	MyUserInterface();
	virtual ~MyUserInterface();

	bool setSTsprite(wstring wszSpriteName);
	bool setMTsprite(wstring wszSpriteName);

	virtual bool frame() override;
};

class MyUIButton : public MyUserInterface
{
public:
	UI_BUTTON_STATE m_bState;
	bool actionFlag;

	MyUIButton();
	~MyUIButton();

	bool frame() override;
};



