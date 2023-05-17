#pragma once
#include "mydxdevicemanager.h"
#include "myshadermanager.h"

using std::vector;
using std::wstring;

struct MyVertex
{
	FLOAT x, y, z;
};

class MyBaseObject
{
protected:
	vector<MyVertex> m_vertices;

	ID3D11Buffer* m_pVertexBuf;
	ID3D11InputLayout* m_pVertexLayout;
	
	MyShader* m_pShader;

	void setVertices();
	HRESULT createVertexBuf();
	HRESULT createVertexLayout();

public:
	MyBaseObject();
	~MyBaseObject();

	bool create(wstring wszShaderFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};