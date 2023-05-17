#include "mytexturemanager.h"

MyTexture::MyTexture()
{
	m_pTexResource = nullptr;
	m_pSRView = nullptr;

	ZeroMemory(&m_tex2dDesc, sizeof(m_tex2dDesc));
}

MyTexture::~MyTexture()
{
	release();
}

HRESULT MyTexture::createTexResourceAndView(wstring wszfileName)
{
	HRESULT hr = S_OK;

	//����̽��� ����̽� ���ؽ�Ʈ�� ���ÿ� �ѱ�� �Ӹ��� �ڵ����� ����� ����.
	hr = DirectX::CreateWICTextureFromFile(I_DEVICE,
		I_DCONTEXT,
		wszfileName.c_str(),
		(ID3D11Resource**)&m_pTexResource,
		&m_pSRView);

	return hr;
}

bool MyTexture::create(wstring wszfileName)
{
	HRESULT hr = S_OK;

	hr = createTexResourceAndView(wszfileName);
	if (FAILED(hr)) { return false; }

	m_pTexResource->GetDesc(&m_tex2dDesc);
	m_szfileName.assign(wszfileName);

	return true;
}

ID3D11ShaderResourceView* MyTexture::getSRView()
{
	return m_pSRView;
}

bool MyTexture::init()
{
	return true;
}

bool MyTexture::frame()
{
	return true;
}

//�ؽ�ó ���ҽ��� ��ǥ�� ����ȭ�� ȭ����ǥ��� �����ϴ�.
bool MyTexture::render()
{
	I_DCONTEXT->PSSetShaderResources(0, 1, &m_pSRView);
	return true;
}

bool MyTexture::release()
{
	if (m_pSRView) { m_pSRView->Release(); m_pSRView = nullptr; }
	if (m_pTexResource) { m_pTexResource->Release(); m_pTexResource = nullptr; }

	return true;
}

MyTexture* MyTextureManager::loadTexture(wstring wszfileName)
{
	map<wstring, MyTexture*>::iterator it = m_textureMap.find(wszfileName);
	if (it != m_textureMap.end()) { return it->second; }
	else
	{
		MyTexture* pNew = new MyTexture;
		if (pNew->create(wszfileName))
		{
			m_textureMap.insert(make_pair(wszfileName, pNew));
		}
		else
		{
			pNew->release();
			pNew = nullptr;
		}
		return pNew;
	}
}

bool MyTextureManager::init()
{
	return true;
}

bool MyTextureManager::frame()
{
	return true;
}

bool MyTextureManager::render()
{
	return true;
}

bool MyTextureManager::release()
{
	for (map<wstring, MyTexture*>::iterator::value_type it : m_textureMap)
	{
		it.second->release();
		it.second = nullptr;
	}

	m_textureMap.clear();

	return true;
}
