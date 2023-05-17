#pragma once
#include "myobject2d.h"
#include "myspritemanager.h"
#include "mycollision.h"

enum UI_STATE { UB_DISABLE, UB_IDLE, UB_PUSH, UB_HOVER, UB_SELECT };

class MyUserInterface : public MyObject2D
{
protected:
	MySingleTextureSprite* m_UISTsprite;
	MyMultiTextureSprite* m_UIMTsprite;

public:
	UI_STATE m_bState;

	MyUserInterface();
	virtual ~MyUserInterface();

	bool setSTsprite(wstring wszSpriteName);
	bool setMTsprite(wstring wszSpriteName);

	virtual bool frame() override;
};

class MyUIButton : public MyUserInterface
{
public:
	MyUIButton();
	~MyUIButton();

	bool frame() override;
};

class MyUIListControl : public MyUserInterface
{
public:
	vector<MyUserInterface*> m_ButtonList;

	MyUIListControl();
	~MyUIListControl();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};



