#include "myeffectstate.h"

MyEffectState::MyEffectState()
{
	m_pSStateWrapPoint = nullptr;
	m_pSStateBorderPoint = nullptr;

	m_pRStateWireFrame = nullptr;
	m_pRStateSolid = nullptr;

	m_pBStateDefault = nullptr;
	m_pBStateAlphaBlend = nullptr;
}

MyEffectState::~MyEffectState()
{
	release();
}

HRESULT MyEffectState::createSStateWrapPoint()
{
	HRESULT hr = S_OK;

	if (!m_pSStateWrapPoint.Get())
	{
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		hr = I_DEVICE->CreateSamplerState(&sd, m_pSStateWrapPoint.GetAddressOf());
	}

	return hr;
}

HRESULT MyEffectState::createSStateBorderPoint()
{
	HRESULT hr = S_OK;

	if (!m_pSStateBorderPoint.Get())
	{
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

		for (int i = 0; i < 4; i++) { sd.BorderColor[i] = 0.5f; }	//gray

		hr = I_DEVICE->CreateSamplerState(&sd, m_pSStateBorderPoint.GetAddressOf());
	}

	return hr;
}

HRESULT MyEffectState::createRStateWireFrame()
{
	HRESULT hr = S_OK;

	if (!m_pRStateWireFrame.Get())
	{
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));

		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;

		hr = I_DEVICE->CreateRasterizerState(&rd, m_pRStateWireFrame.GetAddressOf());
	}

	return hr;
}

HRESULT MyEffectState::createRStateSolid()
{
	HRESULT hr = S_OK;

	if (!m_pRStateSolid.Get())
	{
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));

		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_NONE;

		hr = I_DEVICE->CreateRasterizerState(&rd, m_pRStateSolid.GetAddressOf());
	}

	return hr;
}

HRESULT MyEffectState::createBStateDefault()
{
	HRESULT hr = S_OK;

	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = I_DEVICE->CreateBlendState(&bd, m_pBStateDefault.GetAddressOf());

	return hr;
}

HRESULT MyEffectState::createBStateAlphaBlending()
{
	HRESULT hr = S_OK;

	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = I_DEVICE->CreateBlendState(&bd, m_pBStateAlphaBlend.GetAddressOf());

	return hr;
}

HRESULT MyEffectState::create()
{
	HRESULT hr = S_OK;

	//sampler states
	hr = createSStateWrapPoint();
	if (FAILED(hr)) { return hr; }

	hr = createSStateBorderPoint();
	if (FAILED(hr)) { return hr; }

	//rasterizer states
	hr = createRStateWireFrame();
	if (FAILED(hr)) { return hr; }

	hr = createRStateSolid();
	if (FAILED(hr)) { return hr; }

	//blend states
	hr = createBStateDefault();
	if (FAILED(hr)) { return hr; }

	hr = createBStateAlphaBlending();
	if (FAILED(hr)) { return hr; }

	return hr;
}

bool MyEffectState::init()
{
	return true;
}

bool MyEffectState::frame()
{
	return true;
}

bool MyEffectState::render()
{
	return true;
}

bool MyEffectState::release()
{
	return true;
}
