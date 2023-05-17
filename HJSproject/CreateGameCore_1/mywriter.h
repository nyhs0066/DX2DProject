#pragma once
#include "myrendermanager.h"

class MyWriter
{
public:
	wstring szTargetString;
	D2D1_RECT_F position;

	ID2D1Factory* pD2DFactory;
	IDWriteFactory* pWriteFactory;
	IDWriteTextFormat* pTextFormat;
	ID2D1RenderTarget* pD2DRenderTarget;
	ID2D1SolidColorBrush* pSColorBrush;

	MyWriter();
	~MyWriter();

	HRESULT createD2Factory();
	HRESULT createDWriteFactory();
	HRESULT createTextFormat();
	HRESULT createDSRenderTarget();
	HRESULT createColorBrush();

	//¹ø¿Ü
	IDWriteTextLayout* pTextLayout;
	HRESULT createTextLayout();

	bool create();
	bool init();
	bool frame();
	bool render();
	bool release();

	bool draw(PCWSTR szString, FLOAT stX, FLOAT stY);
};