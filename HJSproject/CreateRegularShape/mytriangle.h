#pragma once
#include "mydxwnd.h"

struct MyVertex4F 
{ 
	FLOAT pos[4];
	FLOAT color[4];
};

class MyTriangle : public MyDxWindow
{
protected:
	vector<MyVertex4F> vertices;

	ID3D11Buffer* pVertexBuf;
	ID3D11InputLayout* pInputLayout;
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;

	ID3DBlob* pVScode;
	ID3DBlob* pPScode;

public:
	MyTriangle();
	~MyTriangle();

	void createRegularShapeVertices(int numOfAngle);
	HRESULT createVBuffer();
	HRESULT createVShader();
	HRESULT createPShader();
	HRESULT createILayout();

	bool init() override;
	bool frame() override;
	bool render() override;
	bool release() override;
	BOOL run() override;
};