#pragma once
#include "mybaseobject.h"

enum MyPlayerState {MYPS_LEFT, MYPS_RIGHT};

class MyPlayer : public MyBaseObject
{
protected:
	FLOAT m_fSpeed;
	MyTexture* m_pMaskTexture;
	MyPlayerState m_pState;

	MyCube m_posRect;
	MyCube m_tRect;

	virtual void setVertices() override;
	virtual void setIndices() override;

	virtual void setTexPos();

public:
	MyPlayer();
	virtual ~MyPlayer();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskTextureFileName, MyCube posRect, MyCube texRect);

	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

	virtual void setPosition(FLOAT stX, FLOAT stY);

	bool setMaskTexture(wstring wszTextureFileName);

	MyCube& getPosRect();
	MyCube& getTexRect();

};