#include "mydevice.h"

myDxDevice::myDxDevice()
{
	pD3Device = nullptr;
	pD3DeviceContext = nullptr;
	pRenderTargetView = nullptr;
	pDXGIFactory = nullptr;
	pAdapter = nullptr;
	pSwapChain = nullptr;
	pBackBuffer = nullptr;
	//pDepthStencil = nullptr;

	ZeroMemory(&D3DViewport, sizeof(D3DViewport));
}

myDxDevice::~myDxDevice()
{
	release();
}

HRESULT myDxDevice::createFactory()
{
	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
}

BOOL myDxDevice::getAdapterList(vector<IDXGIAdapter*>& vAdapterList)
{
	UINT cnt = 0;
	IDXGIAdapter* pTemp;

	while (SUCCEEDED(pDXGIFactory->EnumAdapters(cnt, &pTemp)))
	{
		vAdapterList.push_back(pTemp);
		cnt++;
	}

	if (vAdapterList.size()) { return TRUE; }
	return FALSE;
}

HRESULT myDxDevice::createDevice()
{
	D3D_FEATURE_LEVEL pFeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_10_0
	};

	return D3D11CreateDevice(	pAdapter,
								D3D_DRIVER_TYPE_HARDWARE,
								NULL,
								0,
								pFeatureLevels,
								3,
								D3D11_SDK_VERSION,
								&pD3Device,
								&featureLevel,
								&pD3DeviceContext);
}

HRESULT myDxDevice::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC dxgiSCD;
	ZeroMemory(&dxgiSCD, sizeof(dxgiSCD));

	dxgiSCD.BufferDesc.Width = clientWidth;
	dxgiSCD.BufferDesc.Height = clientHeight;
	dxgiSCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSCD.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSCD.BufferDesc.RefreshRate.Denominator = 1;

	dxgiSCD.SampleDesc.Count = 1;
	dxgiSCD.SampleDesc.Quality = 0;

	dxgiSCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	dxgiSCD.BufferCount = 2;
	
	dxgiSCD.OutputWindow = getHWND();
	dxgiSCD.Windowed = true;
	
	return pDXGIFactory->CreateSwapChain(pD3Device, &dxgiSCD, &pSwapChain);;
}

HRESULT myDxDevice::createRenderTargetView()
{
	HRESULT hr = S_OK;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (SUCCEEDED(hr)) 
	{ 
		hr = pD3Device->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
		if (SUCCEEDED(hr))
		{
			pD3DeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
			return hr;
		}
	}

	return hr;
}

HRESULT myDxDevice::createDepthStencilView()
{	
	return E_NOTIMPL;
}

void myDxDevice::setViewport()
{
	D3DViewport.TopLeftX = 0;
	D3DViewport.TopLeftY = 0;
	D3DViewport.Width = clientWidth;
	D3DViewport.Width = clientHeight;
	D3DViewport.MinDepth = 0;
	D3DViewport.MaxDepth = 1.0f;
	
	pD3DeviceContext->RSSetViewports(1, &D3DViewport);
}

bool myDxDevice::init()
{
	HRESULT hr = S_OK;

	hr = createFactory();
	if (FAILED(hr)) { return false; }

	hr = createDevice();
	if (FAILED(hr)) { return false; }

	hr = createSwapChain();
	if (FAILED(hr)) { return false; }

	hr = createRenderTargetView();
	if (FAILED(hr)) { return false; }

	setViewport();

	return true;
}

bool myDxDevice::frame()
{
	return true;
}

bool myDxDevice::render()
{
	FLOAT color[4] = {0, };
	pD3DeviceContext->ClearRenderTargetView(pRenderTargetView, color);

	pSwapChain->Present(0, 0);

	return true;
}

bool myDxDevice::release()
{
	if (pBackBuffer)		{ pBackBuffer->Release();			pBackBuffer = nullptr; }
	if (pRenderTargetView)	{ pRenderTargetView->Release();		pRenderTargetView = nullptr; }
	if (pSwapChain)			{ pSwapChain->Release();			pSwapChain = nullptr;	}
	if (pDXGIFactory)		{ pDXGIFactory->Release();			pDXGIFactory = nullptr;	}
	if (pD3DeviceContext)	{ pD3DeviceContext->Release();		pD3DeviceContext = nullptr; }
	if (pD3Device)			{ pD3Device->Release();				pD3Device = nullptr; }
	
	ZeroMemory(&D3DViewport, sizeof(D3DViewport));
	ZeroMemory(&featureLevel, sizeof(featureLevel));

	return true;
}

BOOL myDxDevice::run()
{
	if (!init()) { release(); return FALSE; };

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			frame();
			render();
		}
	}

	release();
	return TRUE;
}

LRESULT myDxDevice::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Quit Application?", L"Close Box", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}

			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
