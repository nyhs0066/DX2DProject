#pragma once
#include "mybaseobject.h"

class MyMapObject : public MyBaseObject
{
protected:
	MyCube m_posRect;
	MyCube m_tRect;

	virtual void setVertices() override;
	virtual void setIndices() override;

	virtual void setTexPos();

public:
	MyMapObject();
	virtual ~MyMapObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName
		, UINT stTexX, UINT stTexY, UINT texWidth, UINT texHeight);

	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

	virtual void setPosition(FLOAT stX, FLOAT stY);
};