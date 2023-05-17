#pragma once
#include "mygamecore.h"

using std::vector;
using std::wstring;

struct MyVertex
{
	MyVector3F p;
	MyVector4F c;
	MyVector2F t;
};

struct MyTriangleIndexes { UINT p[3]; };

struct MyRect
{
	MyVector2F pos;
	MyVector2F fWH;
};

class MyVertexPreset
{
public:
	vector<MyVertex> m_vertices;
	vector<MyTriangleIndexes> m_indexes;

	ID3D11Buffer* m_pVertexBuf;
	ID3D11Buffer* m_pIndexBuf;

	MyShader* m_pShader;
	MyTexture* m_pTexture;
	MySamplerState m_SState;

	UINT m_stride;
	UINT m_offset;

	MyVertexPreset();
	~MyVertexPreset();

	bool init();
	bool release();
};

class MyBaseObject2F
{
protected:
	HRESULT createVertexBuf();
	HRESULT createIndexBuf();

	virtual void setVertices();
	virtual void setIndices();

public:
	MyVertexPreset m_VPreset;

	MyRect m_posRect;
	MyRect m_tRect;

	MyBaseObject2F();
	virtual ~MyBaseObject2F();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);

	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

	bool preRender();
	bool postRender();

	virtual void setPosition(FLOAT stX, FLOAT stY);
};