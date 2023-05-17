#pragma once
#include "mytemplatewindow.h"
#include "mybaseobject.h"
#include "mytexture.h"

template <class T>
class Singleton
{
public:
	static T& getInstance()
	{
		static T single;
		return single;
	};
};

class MyDxDeviceManager : public Singleton<MyDxDeviceManager>
{
	friend class Singleton<MyDxDeviceManager>;
private:
	ID3D11Device* pD3Device;
	ID3D11DeviceContext* pD3DContext;
	ID3D11RenderTargetView* pRTView;
	//ID3D11DepthStencilView*			pDepthStencilView;

	IDXGIFactory* pDXGIFactory;
	IDXGISwapChain* pSwapChain;

	ID3D11Texture2D* pBackBuffer;
	///ID3D11Texture2D*					pDepthStencil;

	D3D11_VIEWPORT						D3DViewport;

	int clientWidth, clientHeight;
	HWND hwnd;

	HRESULT							createFactory();
	HRESULT							createDevice();
	HRESULT							createSwapChain();
	HRESULT							createBackBuf();
	HRESULT							createRenderTargetView();
	HRESULT							createDepthStencilView();

	void							setViewport();

	MyDxDeviceManager();
	
public:
	~MyDxDeviceManager();
	ID3D11Device*					getDevice();
	ID3D11DeviceContext*			getDContext();
	bool							create(HWND hwnd, int clientWidth, int clientHeight);

	bool							init();
	bool							frame();
	bool							render();
	bool							release();

	void							preRender();
	HRESULT							postRender();
};

class MyDxWindow : public MyBTWClass<MyDxWindow>
{
public:
	MyDxWindow();
	~MyDxWindow();

	virtual BOOL					run() override;
	LRESULT CALLBACK				MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	PCWSTR							WindowClassName() override;

protected:
	virtual bool					init()		override;
	virtual bool					frame()		override;
	virtual bool					render()	override;
	virtual bool					release()	override;
};