#include "mystate.h"

MyState::MyState()
{
	m_pSamplerState = nullptr;
	m_pBlendState = nullptr;
}

MyState::~MyState()
{
	release();
}

HRESULT MyState::createSmpState()
{
	HRESULT hr = S_OK;

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	//샘플링 필터링 방식을 지정한다.
	//D3D11_FILTER_MIN_MAG_MIP_POINT는 픽셀과 텍셀을 축소(Minimize), 확대(Magnify)의
	//방법으로 텍스처링을 수행한다는 의미
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	//텍셀범위를 벗어난 좌표값의 픽셀에 대한 처리방법을 지정하는 부분이라고 생각하면 편하다.
	//2차원 텍스처의 배열의 경우 W(Z)값에 따라 다른 텍스처를 선택할 수 있기에 3차원 좌표로 구성된다.
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;	//텍스처 텍셀의 X방향 = U
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;	//텍스처 텍셀의 Y방향 = V
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	//텍스처 텍셀의 Z방향 = W

	//unused
	//sd.MipLODBias;
	//sd.MaxAnisotropy;
	//sd.ComparisonFunc;
	
	//D3D11_TEXTURE_ADDRESS_BORDER로 설정된 경우 텍스처 범위의 경계를 벗어난 텍스처에 대해서
	//이 색상을 텍스처 대신 입힌다.
	FLOAT color[4] = { 0.3f, 0.0f, 0.63f, 1.0f };
	for (int i = 0; i < 4; i++) { sd.BorderColor[i] = color[i]; }
	
	//sd.MinLOD;
	//sd.MaxLOD;

	//만든 SamplerState는 PS단계에 바인딩한다.
	hr = I_DEVICE->CreateSamplerState(&sd, &m_pSamplerState);

	return hr;
}

HRESULT MyState::createBlendState()
{
	HRESULT hr = S_OK;

	//TO DO

	return hr;
}

bool MyState::create()
{
	HRESULT hr = S_OK;

	hr = createSmpState();
	if (FAILED(hr)) { return false; }

	//unused
	//hr = createBlendState();
	//if (FAILED(hr)) { return false; }

	return true;
}

bool MyState::init()
{
	return true;
}

bool MyState::frame()
{
	return true;
}

bool MyState::render()
{
	return true;
}

bool MyState::release()
{
	if (m_pSamplerState) { m_pSamplerState->Release(); m_pSamplerState = nullptr; }
	if (m_pBlendState) { m_pBlendState->Release(); m_pBlendState = nullptr; }

	return true;
}

ID3D11SamplerState* MyState::getSamplerState()
{
	return m_pSamplerState;
}

ID3D11BlendState* MyState::getBlendState()
{
	return m_pBlendState;
}
