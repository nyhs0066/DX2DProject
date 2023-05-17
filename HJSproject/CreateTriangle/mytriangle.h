#pragma once
#include "mydevice.h"

struct SimpleVertex 
{ 
	float x, y, z; 
};

class MyTriangle : public myDxDevice
{
protected:
	ID3D11Buffer* pVertexBuf;
	ID3D11InputLayout* pInputLayout;
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;

	ID3DBlob* pVScode;
	ID3DBlob* pPScode;

	UINT vertexNum;

public:
	MyTriangle();
	~MyTriangle();

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