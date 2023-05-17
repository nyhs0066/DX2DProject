#pragma once
#include "mydxdevice.h"

class MyRenderManager : public Singleton<MyRenderManager>
{
	friend class Singleton<MyRenderManager>;
private:
	HWND hwnd;
	int cWidth, cHeight;

	IDXGIFactory* pFactory;
	IDXGISwapChain* pSwapChain;

	ID3D11Texture2D* pBackBuf;
	ID3D11RenderTargetView* pRTView;

	D3D11_VIEWPORT viewport;

	MyRenderManager();
	~MyRenderManager();

	HRESULT							createFactory();
	HRESULT							createSwapChain();
	HRESULT							createBackBuf();
	HRESULT							createRenderTargetView();
	HRESULT							createDepthStencilView();

	void							setViewport();

public:
	bool create(HWND hwnd, int cWidth, int cHeight);
	bool init();
	bool frame();
	bool render();
	bool release();

	void preRender();
	HRESULT postRender();
};

#define PRERENDER Singleton<MyRenderManager>::getInstance().preRender();
#define POSTRENDER Singleton<MyRenderManager>::getInstance().postRender();