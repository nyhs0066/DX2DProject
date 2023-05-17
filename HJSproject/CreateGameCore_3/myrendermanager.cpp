#include "myrendermanager.h"

MyRenderManager::MyRenderManager()
{
	pFactory = nullptr;
	pSwapChain = nullptr;
	pBackBuf = nullptr;
	pRTView = nullptr;

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
}

MyRenderManager::~MyRenderManager()
{
	release();
}

HRESULT MyRenderManager::createFactory()
{
	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
}

HRESULT MyRenderManager::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC dxgiSCD;
	ZeroMemory(&dxgiSCD, sizeof(dxgiSCD));

	dxgiSCD.BufferDesc.Width = MyWindow::cWidth;
	dxgiSCD.BufferDesc.Height = MyWindow::cHeight;
	dxgiSCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSCD.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSCD.BufferDesc.RefreshRate.Denominator = 1;

	dxgiSCD.SampleDesc.Count = 1;
	dxgiSCD.SampleDesc.Quality = 0;

	dxgiSCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//swap chain이 사용할 버퍼의 수 : 2개는 이중 버퍼링에 해당
	dxgiSCD.BufferCount = 2;

	dxgiSCD.OutputWindow = MyWindow::hwnd;
	dxgiSCD.Windowed = true;

	dxgiSCD.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return pFactory->CreateSwapChain(I_DEVICE, &dxgiSCD, &pSwapChain);;
}

HRESULT MyRenderManager::createBackBuf()
{
	HRESULT hr = S_OK;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuf);
	return hr;
}

HRESULT MyRenderManager::createRenderTargetView()
{
	HRESULT hr = S_OK;
	hr = I_DEVICE->CreateRenderTargetView(pBackBuf, nullptr, &pRTView);
	return hr;
}

HRESULT MyRenderManager::createDepthStencilView()
{
	return E_NOTIMPL;
}

void MyRenderManager::setViewport()
{
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = MyWindow::cWidth;
	viewport.Height = MyWindow::cHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

bool MyRenderManager::create()
{
	HRESULT hr = S_OK;

	hr = createFactory();
	if (FAILED(hr)) { return false; }

	hr = createSwapChain();
	if (FAILED(hr)) { return false; }

	hr = createBackBuf();
	if (FAILED(hr)) { return false; }

	hr = createRenderTargetView();
	if (FAILED(hr)) { return false; }

	setViewport();

	return true;
}

bool MyRenderManager::init()
{
	return true;
}

bool MyRenderManager::frame()
{
	return false;
}

bool MyRenderManager::render()
{
	return false;
}

bool MyRenderManager::release()
{
	if (pBackBuf) { pBackBuf->Release();		pBackBuf = nullptr; }
	if (pRTView) { pRTView->Release();			pRTView = nullptr; }
	if (pSwapChain) { pSwapChain->Release();		pSwapChain = nullptr; }
	if (pFactory) { pFactory->Release();		pFactory = nullptr; }
	
	return true;
}

void MyRenderManager::preRender()
{
	I_DCONTEXT->RSSetViewports(1, &viewport);
	I_DCONTEXT->OMSetRenderTargets(1, &pRTView, nullptr);
	FLOAT color[4] = { 0, 0, 0, 1.0f };
	I_DCONTEXT->ClearRenderTargetView(pRTView, color);

	ID3D11SamplerState* pSpst = I_SAMPLERSTATE;
	I_DCONTEXT->PSSetSamplers(0, 1, &pSpst);
}

HRESULT MyRenderManager::postRender()
{
	HRESULT hr = S_OK;
	hr = pSwapChain->Present(0, 0);
	return hr;
}

IDXGISwapChain* MyRenderManager::getSwapChain()
{
	return pSwapChain;
}
