#include "mytexture.h"

HRESULT MyTexture::createTexture()
{
	ID3D11Device* pD3Device = MyDxDeviceManager::getInstance().getDevice();
	ID3D11DeviceContext* pD3DContext = MyDxDeviceManager::getInstance().getDContext();

	HRESULT hr = S_OK;

	hr = CreateWICTextureFromFile(pD3Device,
		pD3DContext,
		L"../../data/003.jpg",
		&pTexture,
		&pSRView);

	return hr;
}

bool MyTexture::init()
{
	HRESULT hr;

	hr = createTexture();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyTexture::frame()
{
	return false;
}

bool MyTexture::render()
{
	ID3D11DeviceContext* pD3DContext = MyDxDeviceManager::getInstance().getDContext();

	pD3DContext->PSSetShaderResources(0, 1, &pSRView);
	return true;
}

bool MyTexture::release()
{
	if (pSRView) { pSRView->Release(); pSRView = nullptr; };
	if (pTexture) { pTexture->Release(); pTexture = nullptr; };

	return true;
}
