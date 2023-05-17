#pragma once
#include "myobject2d.h"
#include "myspritemanager.h"
#include "mycollision.h"

enum UI_STATE { UB_DISABLE, UB_IDLE, UB_PUSH, UB_HOVER, UB_SELECT, UB_MAXSTATE };

class MyUserInterface : public MyObject2D
{
	//UI 텍스처 배열은 info파일로 불러올 때 상태 개수에 맞도록 채워서 로드하는 것을 기본으로 한다.
protected:
	MySprite* m_pSprite;

	vector<MyUserInterface*> m_pChildren;
	vector<MyUserInterface*> m_pParts;

	wstring wszShaderName;
	wstring wszTextureName;

public:
	UI_STATE m_bState;

	MyUserInterface();
	virtual ~MyUserInterface();

	virtual bool create(wstring wszShaderName, wstring wszTextureName);

	void rotate(FLOAT rad, MyVector2F pivot = { 0, 0 });
	bool setSprite(wstring wszSpriteName);

	void partition(FLOAT factorLX, FLOAT factorRX,
		FLOAT factorTY, FLOAT factorBY,
		FLOAT factorLTX, FLOAT factorRTX,
		FLOAT factorTTY, FLOAT factorBTY);

	virtual bool addChild(MyUserInterface* pUI);

	virtual bool release() override;
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
	MyUIListControl();
	~MyUIListControl();

	bool init() override;
	bool frame() override;
	bool render() override;
};

class MyUIDialog : public MyUserInterface
{
public:
	MyVector2F m_vLastMPt;
	BOOL m_bDragFlag;

	MyUIDialog();
	~MyUIDialog();

	bool init() override;
	bool frame() override;
	bool render() override;
};

class MyUIChargeBar : public MyUserInterface
{
public:
	FLOAT m_fCurX;
	FLOAT m_fPosW;
	FLOAT m_fTexW;

	MyUIChargeBar();
	~MyUIChargeBar();

	bool init() override;
	bool frame() override;
	bool render() override;

};