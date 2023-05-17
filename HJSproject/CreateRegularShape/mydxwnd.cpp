#include "mydxwnd.h"

MyDxWindow::MyDxWindow()
{
	pD3Device = nullptr;
	pD3DContext = nullptr;
	pRTView = nullptr;
	pDXGIFactory = nullptr;
	pSwapChain = nullptr;
	pBackBuffer = nullptr;
	//pDepthStencil = nullptr;

	ZeroMemory(&D3DViewport, sizeof(D3DViewport));
}

MyDxWindow::~MyDxWindow()
{
	release();
}

HRESULT MyDxWindow::createFactory()
{
	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);
}

HRESULT MyDxWindow::createDevice()
{
	D3D_FEATURE_LEVEL selectedFL;

	D3D_FEATURE_LEVEL fLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0
	};

	return D3D11CreateDevice(	nullptr,
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

HRESULT MyDxWindow::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC dxgiSCD;
	ZeroMemory(&dxgiSCD, sizeof(dxgiSCD));

	dxgiSCD.BufferDesc.Width =						clientWidth;
	dxgiSCD.BufferDesc.Height =						clientHeight;
	dxgiSCD.BufferDesc.Format =						DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSCD.BufferDesc.RefreshRate.Numerator =		60;
	dxgiSCD.BufferDesc.RefreshRate.Denominator =	1;

	dxgiSCD.SampleDesc.Count =						1;
	dxgiSCD.SampleDesc.Quality =					0;

	dxgiSCD.BufferUsage =							DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//swap chain이 사용할 버퍼의 수 : 2개는 이중 버퍼링에 해당
	dxgiSCD.BufferCount =							2;	
	
	dxgiSCD.OutputWindow =							getHWND();
	dxgiSCD.Windowed =								true;

	dxgiSCD.Flags =									DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	return pDXGIFactory->CreateSwapChain(pD3Device, &dxgiSCD, &pSwapChain);;
}

HRESULT MyDxWindow::createBackBuf()
{
	HRESULT hr = S_OK;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	return hr;
}

HRESULT MyDxWindow::createRenderTargetView()
{
	HRESULT hr = S_OK;
	hr = pD3Device->CreateRenderTargetView(pBackBuffer, nullptr, &pRTView);
	return hr;
}

HRESULT MyDxWindow::createDepthStencilView()
{
	return E_NOTIMPL;
}

void MyDxWindow::setViewport()
{
	D3DViewport.TopLeftX = 0;
	D3DViewport.TopLeftY = 0;
	D3DViewport.Width = clientWidth;
	D3DViewport.Height = clientHeight;
	D3DViewport.MinDepth = 0.0f;
	D3DViewport.MaxDepth = 1.0f;
	
	pD3DContext->RSSetViewports(1, &D3DViewport);
}

bool MyDxWindow::init()
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

bool MyDxWindow::frame()
{
	return true;
}

void MyDxWindow::preRender()
{
	pD3DContext->OMSetRenderTargets(1, &pRTView, nullptr);
	FLOAT color[4] = { 0.0f,0.0f,0.0f,1.0f };
	pD3DContext->ClearRenderTargetView(pRTView, color);
}

bool MyDxWindow::render()
{
	return true;
}

HRESULT MyDxWindow::postRender()
{
	return pSwapChain->Present(0, 0);
}

bool MyDxWindow::release()
{
	if (pBackBuffer)		{ pBackBuffer->Release();		pBackBuffer = nullptr; }
	if (pRTView)			{ pRTView->Release();			pRTView = nullptr; }
	if (pSwapChain)			{ pSwapChain->Release();		pSwapChain = nullptr;	}
	if (pDXGIFactory)		{ pDXGIFactory->Release();		pDXGIFactory = nullptr;	}
	if (pD3DContext)		{ pD3DContext->Release();		pD3DContext = nullptr; }
	if (pD3Device)			{ pD3Device->Release();			pD3Device = nullptr; }

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
	return L"MyDxDevice";
}

ID3D11Device* const MyDxWindow::getDevice() const
{
	return pD3Device;
}

ID3D11DeviceContext* const MyDxWindow::getDContext() const
{
	return pD3DContext;
}

IDXGISwapChain* const MyDxWindow::getSwapChain() const
{
	return pSwapChain;
}
