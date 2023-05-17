#pragma once
#include "mydxwnd.h"

using namespace DirectX;

class MyTexture
{
public:
	ID3D11ShaderResourceView* pSRView;
	ID3D11Resource* pTexture;

public:
	HRESULT createTexture();

	bool init();
	bool frame();
	bool render();
	bool release();
};