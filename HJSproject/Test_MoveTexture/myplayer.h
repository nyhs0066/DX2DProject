#pragma once
#include "mybaseobject.h"

class MyPlayer2F : public MyBaseObject2F
{
protected:
	FLOAT m_fSpeed;
	MyTexture* m_pMaskTexture;

	virtual void setVertices() override;
	virtual void setIndices() override;

	virtual void setTexPos();

public:
	MyPlayer2F();
	virtual ~MyPlayer2F();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskTextureFileName, MyRect posRect, MyRect texRect);

	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

	virtual void setPosition(FLOAT stX, FLOAT stY) override;
};