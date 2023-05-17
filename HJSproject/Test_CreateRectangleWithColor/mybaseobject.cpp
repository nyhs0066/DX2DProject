#include "mybaseobject.h"

MyBaseObject::MyBaseObject()
{
	m_pVertexBuf = nullptr;
	m_pShader = nullptr;
	m_pVertexLayout = nullptr;

	setVertices();
}

MyBaseObject::~MyBaseObject()
{
	release();
}

void MyBaseObject::setVertices()
{
	m_vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } });
	m_vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } });
	m_vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } });
	m_vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } });
	m_vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } });
	m_vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } });
}

HRESULT MyBaseObject::createVertexBuf()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = m_vertices.size() * sizeof(MyVertex);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_vertices.at(0);

	hr = I_DEVICE->CreateBuffer(&bd, &sd, &m_pVertexBuf);

	return hr;
}

HRESULT MyBaseObject::createVertexLayout()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC ieds[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, NULL},
		//{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, NULL}
	};

	hr = I_DEVICE->CreateInputLayout(ieds,
		_ARRAYSIZE(ieds),
		m_pShader->m_pVSCode->GetBufferPointer(),
		m_pShader->m_pVSCode->GetBufferSize(),
		&m_pVertexLayout);

	return hr;
}

bool MyBaseObject::create(wstring wszShaderFileName)
{
	HRESULT hr = S_OK;

	m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_pShader) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createVertexLayout();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyBaseObject::init()
{
	return true;
}

bool MyBaseObject::frame()
{
	return true;
}

bool MyBaseObject::render()
{
	UINT strides = sizeof(MyVertex);
	UINT offset = 0;
	I_DCONTEXT->IASetVertexBuffers(0, 1, &m_pVertexBuf, &strides, &offset);
	I_DCONTEXT->IASetInputLayout(m_pVertexLayout);
	I_DCONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	I_DCONTEXT->VSSetShader(m_pShader->m_pVShader, nullptr, NULL);
	I_DCONTEXT->PSSetShader(m_pShader->m_pPShader, nullptr, NULL);

	//Draw는 인덱스 버퍼가 정의되어 있지 않은 경우 사용
	//DrawIndexed는 인덱스 버퍼가 정의 되어 있는 경우 사용
	I_DCONTEXT->Draw(m_vertices.size(), 0);

	return true;
}

bool MyBaseObject::release()
{
	if (m_pVertexLayout) { m_pVertexLayout->Release(); m_pVertexLayout = nullptr; }
	if (m_pVertexBuf) { m_pVertexBuf->Release(); m_pVertexBuf = nullptr; }

	m_pShader = nullptr;
	
	return true;
}