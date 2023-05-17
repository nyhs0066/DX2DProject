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

	//���ø� ���͸� ����� �����Ѵ�.
	//D3D11_FILTER_MIN_MAG_MIP_POINT�� �ȼ��� �ؼ��� ���(Minimize), Ȯ��(Magnify)��
	//������� �ؽ�ó���� �����Ѵٴ� �ǹ�
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	//�ؼ������� ��� ��ǥ���� �ȼ��� ���� ó������� �����ϴ� �κ��̶�� �����ϸ� ���ϴ�.
	//2���� �ؽ�ó�� �迭�� ��� W(Z)���� ���� �ٸ� �ؽ�ó�� ������ �� �ֱ⿡ 3���� ��ǥ�� �����ȴ�.
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;	//�ؽ�ó �ؼ��� X���� = U
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;	//�ؽ�ó �ؼ��� Y���� = V
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	//�ؽ�ó �ؼ��� Z���� = W

	//unused
	//sd.MipLODBias;
	//sd.MaxAnisotropy;
	//sd.ComparisonFunc;
	
	//D3D11_TEXTURE_ADDRESS_BORDER�� ������ ��� �ؽ�ó ������ ��踦 ��� �ؽ�ó�� ���ؼ�
	//�� ������ �ؽ�ó ��� ������.
	FLOAT color[4] = { 0.3f, 0.0f, 0.63f, 1.0f };
	for (int i = 0; i < 4; i++) { sd.BorderColor[i] = color[i]; }
	
	//sd.MinLOD;
	//sd.MaxLOD;

	//���� SamplerState�� PS�ܰ迡 ���ε��Ѵ�.
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
