#pragma once
#include "myunih.h"

class MyDxDeviceManager : public Singleton<MyDxDeviceManager>
{
	friend class Singleton<MyDxDeviceManager>;
private:
	Microsoft::WRL::ComPtr<IDXGIFactory> m_pDXGIFactory;
	Microsoft::WRL::ComPtr<ID3D11Device> m_pD3D11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pD3D11DeviceContext;

	MyDxDeviceManager();
	~MyDxDeviceManager();

	HRESULT DXGIFactoryCreate();
	HRESULT createDeviceAndDContext();

public:
	HRESULT create();

	bool init();
	bool render();
	bool frame();
	bool release();

	Microsoft::WRL::ComPtr<IDXGIFactory>& getDXGIFactory();
	Microsoft::WRL::ComPtr<ID3D11Device>& getDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& getDeviceContext();
};

#define DEVICE_MANAGER MyDxDeviceManager::getInstance()
#define I_DXGIFACTORY MyDxDeviceManager::getInstance().getDXGIFactory()
#define I_DEVICE MyDxDeviceManager::getInstance().getDevice()
#define I_DCONTEXT MyDxDeviceManager::getInstance().getDeviceContext()