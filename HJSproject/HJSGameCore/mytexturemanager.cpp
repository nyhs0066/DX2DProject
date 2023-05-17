#include "mytexturemanager.h"

MyTexture::MyTexture()
{
	m_pTextureBuf = nullptr;
	m_pSRView = nullptr;

	ZeroMemory(&m_TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
}

MyTexture::~MyTexture()
{
	release();
}

HRESULT MyTexture::create(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = LoadTextureAndCreateSRView(wszFileName);
	if (FAILED(hr)) { return hr; }

	return hr;
}

HRESULT MyTexture::LoadTextureAndCreateSRView(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = DirectX::CreateWICTextureFromFile(I_DEVICE.Get(),
		I_DCONTEXT.Get(),
		wszFileName.c_str(),
		(ID3D11Resource**)m_pTextureBuf.GetAddressOf(),
		m_pSRView.GetAddressOf());

	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(I_DEVICE.Get(),
			I_DCONTEXT.Get(),
			wszFileName.c_str(),
			(ID3D11Resource**)m_pTextureBuf.GetAddressOf(),
			m_pSRView.GetAddressOf());
	}

	if (SUCCEEDED(hr)) 
	{ 
		m_pTextureBuf->GetDesc(&m_TextureDesc); 
		m_TRect = { 0.0f, 0.0f, (FLOAT)m_TextureDesc.Width, (FLOAT)m_TextureDesc.Height };
	}

	return hr;
}

bool MyTexture::init()
{
	return true;
}

bool MyTexture::frame()
{
	return true;
}

bool MyTexture::render()
{
	I_DCONTEXT->PSSetShaderResources(0, 1, m_pSRView.GetAddressOf());
	return true;
}

bool MyTexture::release()
{
	ZeroMemory(&m_TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	return true;
}

MyTextureManager::MyTextureManager()
{

}

MyTextureManager::~MyTextureManager()
{
	release();
}

bool MyTextureManager::init()
{
	return true;
}

bool MyTextureManager::render()
{
	return true;
}

bool MyTextureManager::frame()
{
	return true;
}

bool MyTextureManager::release()
{
	map<wstring, MyTexture*>::iterator it = m_textureMap.begin();

	for (it; it != m_textureMap.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	m_textureMap.clear();

	return true;
}

MyTexture* MyTextureManager::load(wstring wszFileName)
{
	MyTexture* ret = nullptr;

	map<wstring, MyTexture*>::iterator it = m_textureMap.find(wszFileName);

	if (it == m_textureMap.end())
	{
		ret = new MyTexture;
		assert(ret);

		if (FAILED(ret->create(wszFileName)))
		{
			ret->release();
			delete ret;
			ret = nullptr;
		}

		m_textureMap.insert(std::make_pair(wszFileName, ret));
		return ret;
	}
	else
	{
		return it->second;
	}

	return ret;
}

bool MyTextureManager::loadDir(wstring wszDirName)
{
	_wfinddata_t fileData;

	wstring searchPath = wszDirName + L"*.*";
	intptr_t handle = _wfindfirst(searchPath.c_str(), &fileData);

	if (handle != -1)
	{
		do
		{
			if ((fileData.attrib & _A_SUBDIR) && (fileData.name[0] != L'.'))
			{
				loadDir(wszDirName + fileData.name);
			}
			else if (fileData.name[0] != L'.')
			{
				if (!load(wszDirName + fileData.name)) { return false; }
			}
		} while (!_wfindnext(handle, &fileData));

		return true;
	}

	return false;
}
