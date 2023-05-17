#pragma once
#include "mybaseobject.h"

class MyMapObject2F : public MyBaseObject2F
{
protected:
	virtual void setVertices() override;
	virtual void setIndices() override;

public:
	MyMapObject2F();
	virtual ~MyMapObject2F();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName
		, UINT stTexX, UINT stTexY, UINT texWidth, UINT texHeight);

	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

	virtual void setPosition(FLOAT stX, FLOAT stY) override;
	virtual void setTexPos(FLOAT stU, FLOAT stV);
};