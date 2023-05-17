#pragma once
#include "myobject2d.h"

enum MyDirectionState	{ MYPS_LEFT, MYPS_RIGHT };
enum MyActionState		{ MYPS_IDLE, MYPS_WALK, MYPS_JUMP };

class MyPlayer2D : public MyObject2D
{
protected:
	MyDirectionState m_dState;		//direction state
	MyActionState m_aState;			//action state
	BOOL inputFlag;
	FLOAT stateTimer;
	UINT stateCounter;

public:
	vector<vector<wstring>> stateSpriteSet;

	MyPlayer2D();
	virtual ~MyPlayer2D();

	bool init() override;
	bool frame() override;
};