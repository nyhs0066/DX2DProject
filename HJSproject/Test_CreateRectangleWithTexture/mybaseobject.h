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

class MyBaseObject
{
protected:
	vector<MyVertex> m_vertices;

	ID3D11Buffer* m_pVertexBuf;
	ID3D11InputLayout* m_pVertexLayout;
	
	MyShader* m_pShader;
	MyTexture* m_pTexture;
	MySamplerState m_SState;

	void setVertices();
	HRESULT createVertexBuf();
	HRESULT createVertexLayout();

public:
	MyBaseObject();
	~MyBaseObject();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};