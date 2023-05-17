#pragma once
#include "mydxdevicemanager.h"
#include "myshadermanager.h"
#include "myvector.h"
#include "mytexturemanager.h"
#include "myeffectstate.h"

using std::vector;
using std::wstring;

struct MyVertex
{
	MyVector3F pos;
	MyVector4F color;
	MyVector2F texture;
};

struct MyTriangleIndexes { UINT p[3]; };

class MyBaseObject
{
protected:
	vector<MyVertex> m_vertices;
	vector<MyTriangleIndexes> m_indexes;

	ID3D11Buffer* m_pVertexBuf;
	ID3D11Buffer* m_pIndexBuf;
	
	MyShader* m_pShader;
	MyTexture* m_pTexture;
	MySamplerState m_SState;

	void setVertices();
	HRESULT createVertexBuf();
	HRESULT createIndexBuf();

public:
	MyBaseObject();
	~MyBaseObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};