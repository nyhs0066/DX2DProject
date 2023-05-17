#include "myshadermanager.h"

MyShader::MyShader()
{
	m_pVertexLayout = nullptr;
	m_pVShader = nullptr;
	m_pPShader = nullptr;
	m_pVScode = nullptr;
	m_pPScode = nullptr;
}

MyShader::~MyShader()
{
	release();
}

HRESULT MyShader::createVertexLayout()
{
	HRESULT hr = S_OK;

	//구조체 2번째 인수(Sementic index)는 사용자 의미 이름의 번호를 지정한다.
	//		같은 이름의 변수도 숫자 접미를 붙임으로써 사용가능하다는 의미
	// 구조체 4번째 인수(input slot)는 쉐이더가 사용할 변수번호를 지정한다.
	//한도가 존재하니 레퍼런스 참조 할 것
	D3D11_INPUT_ELEMENT_DESC IEDs[] =
	{
		//smt name, smt index, DXGI format, input slot, ele offset, input kind, Data step rate
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, NULL},
	};

	hr = I_DEVICE->CreateInputLayout(IEDs, _ARRAYSIZE(IEDs), m_pVScode->GetBufferPointer(),
		m_pVScode->GetBufferSize(), &m_pVertexLayout);

	return hr;
}

HRESULT MyShader::createVShader(wstring wszFileName)
{
	HRESULT hr = S_OK;
	ID3DBlob* m_pErrBlob = nullptr;

	hr = D3DCompileFromFile(wszFileName.c_str(),
		nullptr, nullptr, 
		"VSmain",
		"vs_5_0",
		0, 0,
		&m_pVScode,
		&m_pErrBlob);

	if (SUCCEEDED(hr))
	{
		hr = I_DEVICE->CreateVertexShader(m_pVScode->GetBufferPointer(), 
			m_pVScode->GetBufferSize(), 
			nullptr,
			&m_pVShader);
	}
	else
	{
		OutputDebugStringA((char*)m_pErrBlob->GetBufferPointer());
		m_pErrBlob->Release();
	}

	return hr;
}

HRESULT MyShader::createPShader(wstring wszFileName)
{
	HRESULT hr = S_OK;
	ID3DBlob* m_pErrBlob = nullptr;

	hr = D3DCompileFromFile(wszFileName.c_str(),
		nullptr, nullptr,
		"PSmain",
		"ps_5_0",
		0, 0,
		&m_pPScode,
		&m_pErrBlob);

	if (SUCCEEDED(hr))
	{
		hr = I_DEVICE->CreatePixelShader(m_pPScode->GetBufferPointer(),
			m_pPScode->GetBufferSize(),
			nullptr,
			&m_pPShader);
	}
	else
	{
		OutputDebugStringA((char*)m_pErrBlob->GetBufferPointer());
		m_pErrBlob->Release();
	}

	return hr;
}

bool MyShader::create(wstring wszFileName)
{
	HRESULT hr = S_OK;

	hr = createVShader(wszFileName);
	if (FAILED(hr)) { return false; }

	hr = createPShader(wszFileName);
	if (FAILED(hr)) { return false; }

	hr = createVertexLayout();
	if (FAILED(hr)) { return false; }

	return true;
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
	I_DCONTEXT->IASetInputLayout(m_pVertexLayout);
	I_DCONTEXT->VSSetShader(m_pVShader, nullptr, 0);

	//unused shader
	//I_DCONTEXT->HSSetShader(nullptr, nullptr, 0);
	//I_DCONTEXT->DSSetShader(nullptr, nullptr, 0);
	//I_DCONTEXT->GSSetShader(nullptr, nullptr, 0);

	I_DCONTEXT->PSSetShader(m_pPShader, nullptr, 0);

	return true;
}

bool MyShader::release()
{
	if (m_pVertexLayout) { m_pVertexLayout->Release(); m_pVertexLayout = nullptr; }
	if (m_pVShader) { m_pVShader->Release(); m_pVShader = nullptr; }
	if (m_pPShader) { m_pPShader->Release(); m_pPShader = nullptr; }
	if (m_pVScode) { m_pVScode->Release(); m_pVScode = nullptr; }
	if (m_pPScode) { m_pPScode->Release(); m_pPScode = nullptr; }

	return true;
}

MyShaderManager::MyShaderManager()
{

}

MyShaderManager::~MyShaderManager()
{
	release();
}

MyShader* MyShaderManager::loadShader(wstring wszFileName)
{
	map<wstring, MyShader*>::iterator it = m_shaderMap.find(wszFileName);

	if (it != m_shaderMap.end()) { return it->second; }
	else
	{
		MyShader* pNew = new MyShader;
		if (pNew->create(wszFileName))
		{
			m_shaderMap.insert(make_pair(wszFileName, pNew));
		}
		else
		{
			pNew->release();
			pNew = nullptr;
		}
		return pNew;
	}
	return nullptr;
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
	return true;
}

