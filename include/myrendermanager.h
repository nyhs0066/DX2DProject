#pragma once
#include "mydxdevicemanager.h"
#include "mywindow.h"

class MyRenderManager : public Singleton<MyRenderManager>
{
	friend class Singleton<MyRenderManager>;
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pBackBuf;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRTView;

	D3D11_VIEWPORT m_ViewPort;
	FLOAT clearColor[4];

	MyRenderManager();
	~MyRenderManager();

	HRESULT createSwapChain();
	HRESULT	createRenderTargetView();

	void setViewPort();

public:
	HRESULT create();

	bool init();
	bool frame();
	bool render();
	bool release();

	bool preRender();
	HRESULT postRender();

	IDXGISwapChain* getSwapChain();
};

#define RENDER_MANAGER		MyRenderManager::getInstance()
#define PRE_RENDER()		MyRenderManager::getInstance().preRender()
#define POST_RENDER()		MyRenderManager::getInstance().postRender()
#define I_SWAPCHAIN			MyRenderManager::getInstance().getSwapChain()
