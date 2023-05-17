#pragma once
#include "mybaseobject.h"
#include "myshape.h"

class MyObject2D : public MyBaseObject
{
protected:
	MyVector2F m_vDirection;
	FLOAT m_fSpeed;
	MyRect m_pRect;
	MyRect m_tRect;

public:
	MyObject2D();
	~MyObject2D();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskFileName, MyRect& pRect, MyRect& tRect);

	virtual bool frame();
	virtual bool render();

	void setPosRect(MyRect& rt);
	void setTexRect(MyRect& rt);

	MyRect& getPosRect();
	MyRect& getTexRect();

	MyVector2F getDirection();
	bool setDirection(MyVector2F vDirection);
};