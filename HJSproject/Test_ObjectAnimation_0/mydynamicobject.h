#pragma once
#include "mybaseobject.h"
#include <random>

class MyDynamicObject : public MyBaseObject
{
protected:
	MyVector3F m_vDirection;
	FLOAT m_fSpeed;
	MyTexture* m_pMaskTexture;

	MyCube m_posRect;
	MyCube m_tRect;

	virtual void setVertices() override;
	virtual void setIndices() override;

	virtual void setTexPos();

public:
	MyDynamicObject();
	virtual ~MyDynamicObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskTextureFileName, MyCube posRect, MyCube texRect);

	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

	virtual void setPosition(FLOAT stX, FLOAT stY);

	MyVector3F getDirection();
	bool setDirection(MyVector3F vDirection);
};