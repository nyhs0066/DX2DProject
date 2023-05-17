#pragma once
#include "myunih.h"
#include <d2d1.h>
#include <dwrite.h>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

using std::wstring;

class MyTextWriter : public Singleton<MyTextWriter>
{
	friend class Singleton<MyTextWriter>;
private:
	Microsoft::WRL::ComPtr<ID2D1Factory>			m_pD2D1Factory;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget>		m_pD2D1RenderTarget;

	Microsoft::WRL::ComPtr<IDWriteFactory>			m_pDWriteFactory;
	Microsoft::WRL::ComPtr<IDWriteTextFormat>		m_pTextFormat;

	Microsoft::WRL::ComPtr<IDXGISurface>			m_pD2RenderTargetBuf;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_pSColorBrush;

	//¹ø¿Ü : TextLayout
	Microsoft::WRL::ComPtr<IDWriteTextLayout>		m_pDWTextLayout;

	MyTextWriter();
	~MyTextWriter();

	HRESULT createD2D1Factory();
	HRESULT createDWriteFactory();
	HRESULT createDWriteTextFormat();
	HRESULT createD2D1RenderTarget(IDXGISwapChain* pSwapChain);
	HRESULT createSolidColorBrush();

	HRESULT createTextLayout();

	bool preRender();
	bool postRender();

public:
	HRESULT create(IDXGISwapChain* pSwapChain);

	bool init();
	bool frame();
	bool render();
	bool release();

	void drawT(wstring wszString, FLOAT stX, FLOAT stY, 
		D2D_COLOR_F color = {1.0f, 1.0f, 1.0f, 1.0f});

	void drawTLayout();
};

#define TEXT_WRITER MyTextWriter::getInstance()
#define DRAWTEXT(s, stX, stY) MyTextWriter::getInstance().drawT(s, stX, stY)