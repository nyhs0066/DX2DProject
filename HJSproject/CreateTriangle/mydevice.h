#pragma once
#include "mytemplatewindow.h"

class myDxDevice : public MyBTWClass<myDxDevice>
{
protected:
	ID3D11Device*				pD3Device;
	ID3D11DeviceContext*		pD3DeviceContext;
	ID3D11RenderTargetView*		pRenderTargetView;
	//ID3D11DepthStencilView*	pDepthStencilView;
	
	IDXGIFactory*				pDXGIFactory;
	IDXGISwapChain*				pSwapChain;

	ID3D11Texture2D*			pBackBuffer;
	///ID3D11Texture2D*			pDepthStencil;

	D3D11_VIEWPORT				D3DViewport;
	D3D_FEATURE_LEVEL			featureLevel;
	
public:
	myDxDevice();
	~myDxDevice();

	HRESULT		createFactory();
	

	HRESULT		createDevice();
	HRESULT		createSwapChain();
	HRESULT		createRenderTargetView();
	HRESULT		createDepthStencilView();
	void		setViewport();

	void				preRender();
	HRESULT				postRender();

	virtual bool		init()		override;
	virtual bool		frame()		override;
	virtual bool		render()	override;
	virtual bool		release()	override;
	virtual BOOL		run()		override;

	LRESULT CALLBACK MessageHandler(
		UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	PCWSTR WindowClassName() override;
};