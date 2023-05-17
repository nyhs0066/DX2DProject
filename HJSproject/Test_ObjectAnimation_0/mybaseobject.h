#pragma once
#include "mygamecore.h"
#include "myshape.h"
#include "mycollision.h"

using std::vector;
using std::wstring;

struct MyVertex
{
	MyVector3F p;
	MyVector4F c;
	MyVector2F t;
};

struct MyTriangleIndexes { UINT p[3]; };

class MyVertexPreset
{
public:
	vector<MyVertex> m_vertices;
	vector<MyTriangleIndexes> m_indexes;

	ID3D11Buffer* m_pVertexBuf;
	ID3D11Buffer* m_pIndexBuf;

	MyShader* m_pShader;
	MyTexture* m_pTexture;

	UINT m_stride;
	UINT m_offset;

	MyVertexPreset();
	~MyVertexPreset();

	bool init();
	bool release();
};

class MyBaseObject
{
protected:
	MyVertexPreset m_VPreset;

	HRESULT createVertexBuf();
	HRESULT createIndexBuf();

	virtual void setVertices();
	virtual void setIndices();

public:
	MyBaseObject();
	virtual ~MyBaseObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);

	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

	bool preRender();
	bool postRender();

	bool setShader(wstring wszShaderFileName);
	bool setTexture(wstring wszTextureFileName);

	bool updateVertexBuffer();
};