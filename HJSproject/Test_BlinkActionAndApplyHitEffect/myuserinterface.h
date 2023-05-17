#pragma once
#include "myobject2d.h"
#include "myspritemanager.h"
#include "mycollision.h"

enum UI_STATE { UB_DISABLE, UB_IDLE, UB_PUSH, UB_HOVER, UB_SELECT, UB_MAXSTATE };

class MyUserInterface : public MyObject2D
{
	//UI �ؽ�ó �迭�� info���Ϸ� �ҷ��� �� ���� ������ �µ��� ä���� �ε��ϴ� ���� �⺻���� �Ѵ�.
protected:
	MySingleTextureSprite* m_UISTsprite;
	MyMultiTextureSprite* m_UIMTsprite;

public:
	UI_STATE m_bState;

	MyUserInterface();
	virtual ~MyUserInterface();

	void rotate(FLOAT rad, MyVector2F pivot = { 0, 0 });
	bool setSTsprite(wstring wszSpriteName);
	bool setMTsprite(wstring wszSpriteName);

	virtual bool frame() override;
	virtual bool addChild(MyUserInterface* pUI);
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
	vector<MyUserInterface*> m_pChildren;

	MyUIListControl();
	~MyUIListControl();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;

	virtual bool addChild(MyUserInterface* pUI);
};

class MyDialog : public MyUserInterface
{
public:
	vector<MyUserInterface*> m_pParts;
	vector<MyUserInterface*> m_pChildren;

	wstring wszShaderName;
	wstring wszTextureName;

	bool create(wstring wszShaderName, wstring wszTextureName);

	MyDialog();
	~MyDialog();

	void partition(	FLOAT factorLX, FLOAT factorRX,
					FLOAT factorTY, FLOAT factorBY,
					FLOAT factorLTX, FLOAT factorRTX,
					FLOAT factorTTY, FLOAT factorBTY);

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;

	virtual bool addChild(MyUserInterface* pUI);
};

