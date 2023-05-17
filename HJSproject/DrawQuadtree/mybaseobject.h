#pragma once
#include "mydxwnd.h"

class MyDxDevicePreset;

struct MyVertex4F 
{ 
	FLOAT pos[4];
	FLOAT color[4];
};

class MyVertexRenderer
{
private:
	static MyVertexRenderer* pMVRenderer;
	ID3D11InputLayout*	pInputLayout;
	ID3D11VertexShader*	pVertexShader;
	ID3D11PixelShader*	pPixelShader;
	ID3DBlob*			pVScode;
	ID3DBlob*			pPScode;

	HRESULT	createVShader();
	HRESULT	createPShader();
	HRESULT	createILayout();

	bool		init();
	bool		release();

	MyVertexRenderer();
	
public:
	~MyVertexRenderer();

	static void create();
	static MyVertexRenderer* getMVRenderer();
	void setLayoutAndShader();
};

class MyBaseObject
{
protected:
	vector<MyVertex4F> vertices;
	ID3D11Buffer* pVertexBuf;
	
public:
	MyBaseObject();
	~MyBaseObject();

	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

private:
	void createRect();
	HRESULT createVBuffer();
};