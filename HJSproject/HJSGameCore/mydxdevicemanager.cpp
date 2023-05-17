#include "mydxdevicemanager.h"

MyDxDeviceManager::MyDxDeviceManager()
{
	m_pDXGIFactory = nullptr;
	m_pD3D11Device = nullptr;
	m_pD3D11DeviceContext = nullptr;
}

MyDxDeviceManager::~MyDxDeviceManager()
{
	release();
}

HRESULT MyDxDeviceManager::DXGIFactoryCreate()
{
	HRESULT hr = S_OK;

	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)m_pDXGIFactory.GetAddressOf());

	return hr;
}

HRESULT MyDxDeviceManager::createDeviceAndDContext()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlag
		= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif //_DEBUG

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_10_0
	};
	D3D_FEATURE_LEVEL selectedFL;

	hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createDeviceFlag,
		featureLevels,
		_ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		m_pD3D11Device.GetAddressOf(),
		&selectedFL,
		m_pD3D11DeviceContext.GetAddressOf()
	);

	return hr;
}

HRESULT MyDxDeviceManager::create()
{
	HRESULT hr = S_OK;

	if (m_pD3D11DeviceContext) { return hr; }

	hr = DXGIFactoryCreate();
	if (FAILED(hr)) { return hr; }

	hr = createDeviceAndDContext();
	if (FAILED(hr)) { return hr; }

	return hr;
}

bool MyDxDeviceManager::init()
{
	return true;
}

bool MyDxDeviceManager::render()
{
	return true;
}

bool MyDxDeviceManager::frame()
{
	return true;
}

bool MyDxDeviceManager::release()
{
	return true;
}

Microsoft::WRL::ComPtr<IDXGIFactory>& MyDxDeviceManager::getDXGIFactory()
{
	return m_pDXGIFactory;
}

Microsoft::WRL::ComPtr<ID3D11Device>& MyDxDeviceManager::getDevice()
{
	return m_pD3D11Device;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext>& MyDxDeviceManager::getDeviceContext()
{
	return m_pD3D11DeviceContext;
}