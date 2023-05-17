#include "myshadermanager.h"

MyShader::MyShader()
{
	m_pVShader = nullptr;
	m_pPShader = nullptr;
	m_pVertexLayout = nullptr;

	m_pVSCode = nullptr;
	m_pPSCode = nullptr;
	m_pErrCode = nullptr;
}

MyShader::~MyShader()
{
	release();
}


HRESULT MyShader::createVShader(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = D3DCompileFromFile(wszFileName.c_str(),
		nullptr,
		nullptr,
		"VS",
		"vs_5_0",
		0, 0,
		m_pVSCode.GetAddressOf(),
		m_pErrCode.GetAddressOf());

	if (SUCCEEDED(hr))
	{
		hr = I_DEVICE->CreateVertexShader(m_pVSCode->GetBufferPointer(),
			m_pVSCode->GetBufferSize(),
			nullptr,
			m_pVShader.GetAddressOf());
	}
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)m_pErrCode->GetBufferPointer());
	}

	return hr;
}

HRESULT MyShader::createPShader(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = D3DCompileFromFile(wszFileName.c_str(),
		nullptr,
		nullptr,
		"PS",
		"ps_5_0",
		0, 0,
		m_pPSCode.GetAddressOf(),
		m_pErrCode.GetAddressOf());

	if (SUCCEEDED(hr))
	{
		hr = I_DEVICE->CreatePixelShader(m_pPSCode->GetBufferPointer(),
			m_pPSCode->GetBufferSize(),
			nullptr,
			m_pPShader.GetAddressOf());
	}
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)m_pErrCode->GetBufferPointer());
	}

	return hr;
}

HRESULT MyShader::createVertexLayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC ieds[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, NULL}
	};

	hr = I_DEVICE->CreateInputLayout(ieds,
		_ARRAYSIZE(ieds),
		m_pVSCode->GetBufferPointer(),
		m_pVSCode->GetBufferSize(),
		m_pVertexLayout.GetAddressOf());

	return hr;
}

HRESULT MyShader::create(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = createVShader(wszFileName);
	if (FAILED(hr)) { return hr; }

	hr = createPShader(wszFileName);
	if (FAILED(hr)) { return hr; }

	hr = createVertexLayout();
	if (FAILED(hr)) { return hr; }

	return hr;
}

bool MyShader::init()
{
	return true;
}

bool MyShader::frame()
{
	return true;
}

bool MyShader::render()
{
	I_DCONTEXT->IASetInputLayout(m_pVertexLayout.Get());
	I_DCONTEXT->VSSetShader(m_pVShader.Get(), nullptr, NULL);
	I_DCONTEXT->PSSetShader(m_pPShader.Get(), nullptr, NULL);
	return true;
}

bool MyShader::release()
{
	return true;
}

MyShaderManager::MyShaderManager() {}

MyShaderManager::~MyShaderManager()
{
	release();
}

MyShader* MyShaderManager::load(wstring wszFileName)
{
	HRESULT hr = S_OK;

	map<wstring, MyShader*>::iterator it = m_shaderMap.find(wszFileName);

	if (it == m_shaderMap.end())
	{
		MyShader* newE = new MyShader;

		hr = newE->create(wszFileName);
		if (FAILED(hr))
		{
			delete newE;
			newE = nullptr;
		}

		m_shaderMap.insert(std::make_pair(wszFileName, newE));

		return newE;
	}
	else { return it->second; }
}

bool MyShaderManager::loadDir(wstring wszDirName)
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

bool MyShaderManager::init()
{
	return true;
}

bool MyShaderManager::frame()
{
	return true;
}

bool MyShaderManager::render()
{
	return true;
}

bool MyShaderManager::release()
{
	for (map<wstring, MyShader*>::iterator::value_type it : m_shaderMap)
	{
		delete it.second;
		it.second = nullptr;
	}

	m_shaderMap.clear();

	return true;
}

