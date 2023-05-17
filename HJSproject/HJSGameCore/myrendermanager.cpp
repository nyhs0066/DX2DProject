#include "myrendermanager.h"

MyRenderManager::MyRenderManager()
{
	m_pSwapChain = nullptr;
	m_pRTView = nullptr;

	ZeroMemory(&m_ViewPort, sizeof(D3D11_VIEWPORT));
}

MyRenderManager::~MyRenderManager()
{
	release();
}

HRESULT MyRenderManager::createSwapChain()
{
	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = MyWindow::cWidth;
	scd.BufferDesc.Height = MyWindow::cHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;

	scd.OutputWindow = MyWindow::hwnd;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = I_DXGIFACTORY->CreateSwapChain(I_DEVICE.Get(), &scd, m_pSwapChain.GetAddressOf());

	return hr;
}

HRESULT	MyRenderManager::createRenderTargetView()
{
	HRESULT hr = S_OK;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pBackBuf;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_pBackBuf.GetAddressOf());
	if (SUCCEEDED(hr)) 
	{ 
		hr = I_DEVICE->CreateRenderTargetView(m_pBackBuf.Get(), nullptr, m_pRTView.GetAddressOf());
	}

	return hr;
}

void MyRenderManager::setViewPort()
{
	m_ViewPort.TopLeftX = 0.0f;
	m_ViewPort.TopLeftY = 0.0f;
	m_ViewPort.Width = MyWindow::cWidth;
	m_ViewPort.Height = MyWindow::cHeight;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}

void MyRenderManager::setViewPort(FLOAT width, FLOAT height)
{
	m_ViewPort.TopLeftX = 0.0f;
	m_ViewPort.TopLeftY = 0.0f;
	m_ViewPort.Width = width;
	m_ViewPort.Height = height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}


HRESULT MyRenderManager::create()
{
	HRESULT hr = S_OK;

	if (m_pRTView.Get()) { return hr; }

	if (!I_DXGIFACTORY.Get())
	{
		hr = DEVICE_MANAGER.create();
		if (FAILED(hr)) { return hr; }
	}

	hr = createSwapChain();
	if (FAILED(hr)) { return hr; }

	hr = createRenderTargetView();
	if (FAILED(hr)) { return hr; }

	return hr;
}

bool MyRenderManager::init()
{
	for (int i = 0; i < 4; i++) { clearColor[i] = 0.0f; }
	setViewPort();

	return true;
}

bool MyRenderManager::frame()
{
	return true;
}

bool MyRenderManager::render()
{
	return true;
}

bool MyRenderManager::release()
{
	ZeroMemory(&m_ViewPort, sizeof(D3D11_VIEWPORT));

	return true;
}

bool MyRenderManager::preRender()
{
	I_DCONTEXT->RSSetViewports(1, &m_ViewPort);
	I_DCONTEXT->OMSetRenderTargets(1, m_pRTView.GetAddressOf(), nullptr);
	I_DCONTEXT->ClearRenderTargetView(m_pRTView.Get(), clearColor);

	return true;
}

HRESULT MyRenderManager::postRender()
{
	//전달 인수는 수직 동기화 신호와 관련있음
	return m_pSwapChain->Present(0, 0);
}

HRESULT MyRenderManager::resizeRenderTarget(FLOAT cWidth, FLOAT cHeight)
{
	HRESULT hr = S_OK;

	I_DCONTEXT->OMSetRenderTargets(0, NULL, NULL);
	m_pRTView.Reset();

	DXGI_SWAP_CHAIN_DESC prevBD;

	hr = m_pSwapChain->GetDesc(&prevBD);
	prevBD.BufferDesc.Width = cWidth;
	prevBD.BufferDesc.Height = cHeight;

	hr = m_pSwapChain->ResizeTarget(&prevBD.BufferDesc);

	hr = createRenderTargetView();
	if (FAILED(hr)) { return hr; }

	//setViewPort();

	return hr;
}

IDXGISwapChain* MyRenderManager::getSwapChain()
{
	return m_pSwapChain.Get();
}