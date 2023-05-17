#pragma once
#include "mywindow.h"
#include "mydxdevice.h"
#

class MyRenderManager : public Singleton<MyRenderManager>
{
	friend class Singleton<MyRenderManager>;
private:
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
	bool							create();
	bool							init();
	bool							frame();
	bool							render();
	bool							release();

	void							preRender();
	HRESULT							postRender();

	IDXGISwapChain*					getSwapChain();
};

#define PRE_RENDER() MyRenderManager::getInstance().preRender()
#define POST_RENDER() MyRenderManager::getInstance().postRender()
#define I_SWAPCHAIN() MyRenderManager::getInstance().getSwapChain()