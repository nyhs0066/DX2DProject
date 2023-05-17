#pragma once
#include "mytemplatewindow.h"

class myDxDevice : public MyDTWindow
{
protected:
	ID3D11Device*				pD3Device;
	ID3D11DeviceContext*		pD3DeviceContext;
	ID3D11RenderTargetView*		pRenderTargetView;
	//ID3D11DepthStencilView*	pDepthStencilView;
	
	IDXGIFactory*				pDXGIFactory;
	IDXGIAdapter*				pAdapter;
	vector<IDXGIAdapter*>		vAdapterList;
	IDXGISwapChain*				pSwapChain;

	ID3D11Texture2D*			pBackBuffer;
	///ID3D11Texture2D*			pDepthStencil;

	D3D11_VIEWPORT				D3DViewport;
	D3D_FEATURE_LEVEL			featureLevel;
	
public:
	myDxDevice();
	~myDxDevice();

	HRESULT		createFactory();
	BOOL		getAdapterList(vector<IDXGIAdapter*>& vAdapterList);

	HRESULT		createDevice();
	HRESULT		createSwapChain();
	HRESULT		createRenderTargetView();
	HRESULT		createDepthStencilView();
	void		setViewport();

	bool		init();
	bool		frame();
	bool		render();
	bool		release();
	BOOL		run();

	LRESULT CALLBACK MessageHandler(
		UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};