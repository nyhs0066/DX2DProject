#pragma once
#include "myrendermanager.h"

class MyWriter : public Singleton<MyWriter>
{
	friend class Singleton<MyWriter>;
private:
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
public:
	bool create();

	bool init();
	bool frame();
	bool render();
	bool release();

	bool draw(wstring wszString, FLOAT stX, FLOAT stY);
};

#define DRAW_TEXT(wszString, stX, stY) MyWriter::getInstance().draw((wszString), (stX), (stY))