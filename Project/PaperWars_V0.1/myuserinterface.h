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
	vector<MyUserInterface*> m_pParts;

	wstring wszShaderName;
	wstring wszTextureName;

public:
	UI_STATE m_bState;
	bool m_bAvailableFlag;
	vector<MyUserInterface*> m_pChild;

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
	virtual MyUserInterface* getChild(int idx);

	virtual bool release() override;
};

class MyUIButton : public MyUserInterface
{
public:
	MySound* S_button_hover;
	MySound* S_button_Select;

	MyUIButton();
	~MyUIButton();

	bool frame() override;
	bool render() override;
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

class MyShopDialog : public MyUIDialog
{
public:
	bool render() override;
};

class MyStackBar : public MyUserInterface
{
public:
	FLOAT m_fPosW;
	FLOAT m_fTexW;
	FLOAT m_fCurStack;
	FLOAT m_fMaxStack;

	BOOL m_bMaxFlag;

	MyObject2D m_barFrame;

	MyStackBar();
	~MyStackBar();

	void gradeUp();

	bool init() override;
	bool postFrame(FLOAT radian = 0.0f) override;
	bool render() override;
};