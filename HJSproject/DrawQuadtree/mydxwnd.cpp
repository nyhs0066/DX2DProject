#include "mydxwnd.h"

MyDxDevicePreset* MyDxDevicePreset::pMDXDevice = nullptr;

MyDxDevicePreset::MyDxDevicePreset(HWND hwnd, int clientWidth, int clientHeight)
{
	pD3Device = nullptr;
	pD3DContext = nullptr;
	pRTView = nullptr;
	pDXGIFactory = nullptr;
	pSwapChain = nullptr;
	pBackBuffer = nullptr;
	//pDepthStencil = nullptr;

	ZeroMemory(&D3DViewport, sizeof(D3DViewport));

	this->hwnd = hwnd;
	this->clientWidth = clientWidth;
	this->clientHeight = clientHeight;

	init();
}

MyDxDevicePreset::~MyDxDevicePreset()
{
	release();
}

void MyDxDevicePreset::create(HWND hwnd, int clientWidth, int clientHeight)
{
	if (!pMDXDevice) { pMDXDevice = new MyDxDevicePreset(hwnd, clientWidth, clientHeight); }
}

ID3D11Device* MyDxDevicePreset::getDevice()
{
	return pMDXDevice->pD3Device;
}

ID3D11DeviceContext* MyDxDevicePreset::getDContext()
{
	return pMDXDevice->pD3DContext;
}

HRESULT MyDxDevicePreset::createFactory()
{
	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
}

HRESULT MyDxDevicePreset::createDevice()
{
	D3D_FEATURE_LEVEL selectedFL;

	D3D_FEATURE_LEVEL fLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0
	};

	return D3D11CreateDevice(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		fLevels,
		_ARRAYSIZE(fLevels),		//winnt.h
		D3D11_SDK_VERSION,
		&pD3Device,
		&selectedFL,
		&pD3DContext);
}

HRESULT MyDxDevicePreset::createSwapChain()
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

	//swap chain이 사용할 버퍼의 수 : 2개는 이중 버퍼링에 해당
	dxgiSCD.BufferCount = 2;

	dxgiSCD.OutputWindow = hwnd;
	dxgiSCD.Windowed = true;

	dxgiSCD.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return pDXGIFactory->CreateSwapChain(pD3Device, &dxgiSCD, &pSwapChain);;
}

HRESULT MyDxDevicePreset::createBackBuf()
{
	HRESULT hr = S_OK;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	return hr;
}

HRESULT MyDxDevicePreset::createRenderTargetView()
{
	HRESULT hr = S_OK;
	hr = pD3Device->CreateRenderTargetView(pBackBuffer, nullptr, &pRTView);
	return hr;
}

HRESULT MyDxDevicePreset::createDepthStencilView()
{
	return E_NOTIMPL;
}

void MyDxDevicePreset::setViewport()
{
	D3DViewport.TopLeftX = 0;
	D3DViewport.TopLeftY = 0;
	D3DViewport.Width = clientWidth;
	D3DViewport.Height = clientHeight;
	D3DViewport.MinDepth = 0.0f;
	D3DViewport.MaxDepth = 1.0f;

	pD3DContext->RSSetViewports(1, &D3DViewport);
}

bool MyDxDevicePreset::init()
{
	if (!pD3Device)
	{
		HRESULT hr = S_OK;

		hr = createFactory();
		if (FAILED(hr)) { return false; }

		hr = createDevice();
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
	return true;
}

bool MyDxDevicePreset::release()
{
	if (pBackBuffer) { pBackBuffer->Release();		pBackBuffer = nullptr; }
	if (pRTView) { pRTView->Release();			pRTView = nullptr; }
	if (pSwapChain) { pSwapChain->Release();		pSwapChain = nullptr; }
	if (pDXGIFactory) { pDXGIFactory->Release();		pDXGIFactory = nullptr; }
	if (pD3DContext) { pD3DContext->Release();		pD3DContext = nullptr; }
	if (pD3Device) { pD3Device->Release();			pD3Device = nullptr; }

	return true;
}

void MyDxDevicePreset::preRender()
{
	getDContext()->OMSetRenderTargets(1, &pRTView, nullptr);
	FLOAT color[4] = { 0.0f,0.0f,0.0f,1.0f };
	getDContext()->ClearRenderTargetView(pRTView, color);
}

HRESULT MyDxDevicePreset::postRender()
{
	return pSwapChain->Present(0, 0);
}

MyDxWindow::MyDxWindow()
{
	
}

MyDxWindow::~MyDxWindow()
{
	release();
}

bool MyDxWindow::init()
{
	MyDxDevicePreset::create(hwnd, clientWidth, clientHeight);
	MyVertexRenderer::create();

	return true;
}

bool MyDxWindow::frame()
{
	return true;
}

bool MyDxWindow::render()
{
	MyDxDevicePreset::pMDXDevice->preRender();
	
	//TO DO
	MyBaseObject NE;
	NE.createVBuffer();
	NE.render();

	MyDxDevicePreset::pMDXDevice->postRender();
	return true;
}

bool MyDxWindow::release()
{
	return true;
}

BOOL MyDxWindow::run()
{
	if (!init()) { release(); return FALSE; };

	MSG msg = { 0 };
	BOOL runFlag = TRUE;

	while (TRUE)
	{
		if (msg.message == WM_QUIT) { break; }

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!frame() || !render()) 
			{ 
				runFlag = FALSE; break;
			}
		}
	}

	release();

	return runFlag;
}

LRESULT MyDxWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

PCWSTR MyDxWindow::WindowClassName()
{
	return L"MyDxDevicePreset";
}