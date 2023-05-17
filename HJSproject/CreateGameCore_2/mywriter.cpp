#include "mywriter.h"

MyWriter::MyWriter()
{
	pD2DFactory = nullptr;
	pWriteFactory = nullptr;
	pTextFormat = nullptr;
	pD2DRenderTarget = nullptr;
	pSColorBrush = nullptr;
	pTextLayout = nullptr;
}

MyWriter::~MyWriter()
{
}

HRESULT MyWriter::createD2Factory()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	return hr;
}

HRESULT MyWriter::createDWriteFactory()
{
	HRESULT hr = S_OK;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), (IUnknown**)&pWriteFactory);

	return hr;
}

HRESULT MyWriter::createTextFormat()
{
	HRESULT hr = S_OK;

	hr = pWriteFactory->CreateTextFormat(
		L"consolas",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15,
		L"en-us",
		&pTextFormat);

	return hr;
}

HRESULT MyWriter::createDSRenderTarget()
{
	HRESULT hr = S_OK;

	IDXGISurface* pSurfaceBuf = nullptr;
	hr = I_SWAPCHAIN->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pSurfaceBuf);
	if (FAILED(hr)) { return hr; }

	D2D1_RENDER_TARGET_PROPERTIES rtProps;

	rtProps.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtProps.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	rtProps.dpiX = rtProps.dpiY = 96.0f;
	rtProps.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtProps.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	hr = pD2DFactory->CreateDxgiSurfaceRenderTarget(pSurfaceBuf,
		&rtProps, &pD2DRenderTarget);

	return hr;
}

HRESULT MyWriter::createColorBrush()
{
	HRESULT hr = S_OK;

	D2D_COLOR_F color = { 1.0f, 1.0f, 1.0f, 1.0f };
	hr = pD2DRenderTarget->CreateSolidColorBrush(color, &pSColorBrush);

	return hr;
}

HRESULT MyWriter::createTextLayout()
{
	HRESULT hr = S_OK;

	wstring test = L"TEST";

	hr = pWriteFactory->CreateTextLayout(test.c_str(),
		test.size(),
		pTextFormat,
		300, 300,
		&pTextLayout
	);

	return hr;
}

bool MyWriter::create()
{
	HRESULT hr = S_OK;

	hr = createD2Factory();
	if (FAILED(hr)) { return false; }

	hr = createDWriteFactory();
	if (FAILED(hr)) { return false; }

	hr = createTextFormat();
	if (FAILED(hr)) { return false; }

	hr = createDSRenderTarget();
	if (FAILED(hr)) { return false; }

	hr = createColorBrush();
	if (FAILED(hr)) { return false; }

	hr = createTextLayout();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyWriter::init()
{
	return true;
}

bool MyWriter::frame()
{
	return true;
}

bool MyWriter::render()
{
	return true;
}

bool MyWriter::release()
{
	if (pTextLayout) { pTextLayout->Release();  pTextLayout = nullptr; }
	if (pSColorBrush) { pSColorBrush->Release(); pSColorBrush = nullptr; }
	if (pD2DRenderTarget) { pD2DRenderTarget->Release(); pD2DRenderTarget = nullptr; }
	if (pTextFormat) { pTextFormat->Release(); pTextFormat = nullptr; }
	if (pWriteFactory) { pWriteFactory->Release(); pWriteFactory = nullptr; }
	if (pD2DFactory) { pD2DFactory->Release(); pD2DFactory = nullptr; }

	return true;
}

bool MyWriter::draw(wstring wszString, FLOAT stX, FLOAT stY)
{
	D2D_RECT_F pos = { stX, stY, (float)MyWindow::cWidth, (float)MyWindow::cHeight };

	pD2DRenderTarget->BeginDraw();

	pD2DRenderTarget->DrawText(wszString.c_str(), wszString.size(),
		pTextFormat, pos, pSColorBrush);

	pD2DRenderTarget->EndDraw();

	return true;
}
