#pragma once
#include "mytemplatewindow.h"

class MyDxWindow : public MyBTWClass<MyDxWindow>
{
private:
	ID3D11Device*				pD3Device;
	ID3D11DeviceContext*		pD3DContext;
	ID3D11RenderTargetView*		pRTView;
	//ID3D11DepthStencilView*	pDepthStencilView;
	
	IDXGIFactory*				pDXGIFactory;
	IDXGISwapChain*				pSwapChain;

	ID3D11Texture2D*			pBackBuffer;
	///ID3D11Texture2D*			pDepthStencil;

	D3D11_VIEWPORT				D3DViewport;
	
public:
	MyDxWindow();
	~MyDxWindow();

	void							setViewport();
	
	void							preRender();
	HRESULT							postRender();

	virtual BOOL					run() override;

	LRESULT CALLBACK				MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	PCWSTR							WindowClassName() override;

	ID3D11Device*			const	getDevice()			const;
	ID3D11DeviceContext*	const	getDContext()	const;
	IDXGISwapChain*			const	getSwapChain()		const;

protected:
	virtual bool					init()		override;
	virtual bool					frame()		override;
	virtual bool					render()	override;
	virtual bool					release()	override;

private:
	HRESULT							createFactory();
	HRESULT							createDevice();
	HRESULT							createSwapChain();
	HRESULT							createBackBuf();
	HRESULT							createRenderTargetView();
	HRESULT							createDepthStencilView();
};