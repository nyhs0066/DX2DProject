#pragma once
#include "myrendermanager.h"
#include "mytexturemanager.h"
#include "myshadermanager.h"
#include "myvector.h"

class MyBaseObject
{
protected:
	vector<MyVertex>	vertices;
	ID3D11Buffer*		pVertexBuf;
	MyTexture*			pObjTexture;
	MyShader*			pObjShader;

public:
	MyBaseObject();
	virtual ~MyBaseObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);

	virtual bool init() = 0;
	virtual bool frame() = 0;
	virtual bool render() = 0;
	virtual bool release();

	bool preRender();
	bool postRender();
};

class MyRectObject : public MyBaseObject
{
protected:
	MyVector2F pos;
	MyVector2F fWH;

public:
	MyRectObject();
	~MyRectObject();

	bool setRect(MyVector2F pos, MyVector2F fWH);
	bool setPosition(MyVector2F nPos);

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};