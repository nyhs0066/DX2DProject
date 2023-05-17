#include "mydxdevice.h"

MyDXDevice::MyDXDevice()
{
	pDevice = nullptr;
	pDContext = nullptr;
}

MyDXDevice::~MyDXDevice()
{
	release();
}

bool MyDXDevice::create()
{
	HRESULT hr = S_OK;

	UINT flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;	//D2D기능 사용을 위한 플래그 : RGB역순 사용

	D3D_FEATURE_LEVEL selectedFL;

	D3D_FEATURE_LEVEL fLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0
	};

	hr = D3D11CreateDevice(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flag,
		fLevels,
		_ARRAYSIZE(fLevels),		//winnt.h
		D3D11_SDK_VERSION,
		&pDevice,
		&selectedFL,
		&pDContext);

	if (FAILED(hr)) { return false; }
	return true;
}

bool MyDXDevice::init()
{
	return true;
}

bool MyDXDevice::release()
{
	if (pDevice) { pDevice->Release(); pDevice = nullptr; }
	if (pDContext) { pDContext->Release(); pDContext = nullptr; }
	return true;
}

ID3D11Device* MyDXDevice::getDevice()
{
	return pDevice;
}

ID3D11DeviceContext* MyDXDevice::getDContext()
{
	return pDContext;
}
