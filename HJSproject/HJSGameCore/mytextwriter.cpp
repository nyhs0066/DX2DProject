#include "mytextwriter.h"

MyTextWriter::MyTextWriter()
{
	m_pD2D1Factory = nullptr;
	m_pD2D1RenderTarget = nullptr;

	m_pDWriteFactory = nullptr;
	m_pTextFormat = nullptr;

	m_pD2RenderTargetBuf = nullptr;
	m_pSColorBrush = nullptr;

	m_pDWTextLayout = nullptr;
}

MyTextWriter::~MyTextWriter()
{
	release();
}

HRESULT MyTextWriter::createD2D1Factory()
{
	HRESULT hr = S_OK;

	//D2D1_FACTORY_TYPE : 팩토리의 다른 스레드 옵션 타입
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_pD2D1Factory.GetAddressOf());

	return hr;
}

HRESULT MyTextWriter::createDWriteFactory()
{
	HRESULT hr = S_OK;

	//DWRITE_FACTORY_TYPE : 팩토리의 프로세스간 공유 옵션 타입
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)m_pDWriteFactory.GetAddressOf());

	return hr;
}

HRESULT MyTextWriter::createDWriteTextFormat()
{
	HRESULT hr = S_OK;

	hr = m_pDWriteFactory->CreateTextFormat(
		L"consolas",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15,
		L"en-us",
		m_pTextFormat.GetAddressOf());

	return hr;
}

HRESULT MyTextWriter::createD2D1RenderTarget(IDXGISwapChain* pSwapChain)
{
	HRESULT hr = S_OK;

	if (!pSwapChain) { hr = STG_E_INVALIDPOINTER; return hr; }

	hr = pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)m_pD2RenderTargetBuf.GetAddressOf());
	if (SUCCEEDED(hr)) 
	{ 
		D2D1_RENDER_TARGET_PROPERTIES rtp;

		rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
		rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		rtp.dpiX = 96;
		rtp.dpiY = 96;
		rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

		hr = m_pD2D1Factory->CreateDxgiSurfaceRenderTarget(
			m_pD2RenderTargetBuf.Get(),
			&rtp,
			m_pD2D1RenderTarget.GetAddressOf());
	}

	return hr;
}

HRESULT MyTextWriter::createSolidColorBrush()
{
	HRESULT hr = S_OK;

	hr = m_pD2D1RenderTarget->CreateSolidColorBrush({ 1.0f, 1.0f, 1.0f, 1.0f }, m_pSColorBrush.GetAddressOf());

	return hr;
}

HRESULT MyTextWriter::createTextLayout()
{
	HRESULT hr = S_OK;

	wstring defaultString = L"테스트 텍스트";
	hr = m_pDWriteFactory->CreateTextLayout(defaultString.c_str(),
		defaultString.size(),
		m_pTextFormat.Get(),
		100.0f, 100.0f,
		m_pDWTextLayout.GetAddressOf());

	return hr;
}

bool MyTextWriter::preRender()
{
	m_pD2D1RenderTarget->BeginDraw();
	return true;
}

bool MyTextWriter::postRender()
{

	m_pD2D1RenderTarget->EndDraw();
	return true;
}

HRESULT MyTextWriter::create(IDXGISwapChain* pSwapChain)
{
	HRESULT hr = S_OK;

	hr = createD2D1Factory();
	if (FAILED(hr)) { return hr; }

	hr = createDWriteFactory();
	if (FAILED(hr)) { return hr; }

	hr = createDWriteTextFormat();
	if (FAILED(hr)) { return hr; }

	hr = createD2D1RenderTarget(pSwapChain);
	if (FAILED(hr)) { return hr; }

	hr = createSolidColorBrush();
	if (FAILED(hr)) { return hr; }

	hr = createTextLayout();
	if (FAILED(hr)) { return hr; }

	return hr;
}

bool MyTextWriter::init()
{
	m_pSColorBrush->SetColor({ 0.5f, 0.5f, 0.5f, 1.0f });
	return true;
}

bool MyTextWriter::frame()
{
	return true;
}

bool MyTextWriter::render()
{
	return true;
}

bool MyTextWriter::release()
{
	return true;
}

void MyTextWriter::drawT(wstring wszString, FLOAT stX, FLOAT stY, D2D_COLOR_F color)
{
	preRender();

	D2D1_RECT_F position = { stX , stY , stX + 200.0f, stY + 200.0f };
	m_pSColorBrush->SetColor(color);

	m_pD2D1RenderTarget->DrawText(wszString.c_str(),
		wszString.size(),
		m_pTextFormat.Get(),
		position,
		m_pSColorBrush.Get());

	postRender();
}

void MyTextWriter::drawTLayout()
{
	preRender();

	m_pD2D1RenderTarget->DrawTextLayout({ 0.0f, 0.0f },
		m_pDWTextLayout.Get(),
		m_pSColorBrush.Get());

	postRender();
}



