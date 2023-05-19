#include "mybaseobject.h"

MyVertexPreset::MyVertexPreset()
{
	init();
}

MyVertexPreset::~MyVertexPreset()
{
	release();
}

bool MyVertexPreset::init()
{
	ZeroMemory(this, sizeof(MyVertexPreset));

	m_stride = sizeof(MyVertex);
	m_offset = 0;
	return true;
}

bool MyVertexPreset::release()
{
	m_pShader = nullptr;
	m_pTexture = nullptr;

	m_vertices.clear();
	m_indexes.clear();

	return true;
}

MyBaseObject::MyBaseObject()
{
	//MyVertexPreset은 생성시 자동 초기화

	setVertices();
	setIndices();
}

MyBaseObject::~MyBaseObject()
{
	release();
}

void MyBaseObject::setVertices()
{
	//정점 좌표 : NDC(Normalized Device Coordinate)
	//색상 포맷 : (R32 G32 B32 A32) FLOAT
	//텍셀 좌표 : NSC(Normalized Screen Coordinate)

	for (int i = 0; i < 4; i++) { m_VPreset.m_vertices.push_back(MyVertex()); };

	m_VPreset.m_vertices[0].p = { -1.0f, 1.0f, 0.0f };
	m_VPreset.m_vertices[1].p = { 1.0f, 1.0f, 0.0f };
	m_VPreset.m_vertices[2].p = { -1.0f, -1.0f, 0.0f };
	m_VPreset.m_vertices[3].p = { 1.0f, -1.0f, 0.0f };

	m_VPreset.m_vertices[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VPreset.m_vertices[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VPreset.m_vertices[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VPreset.m_vertices[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_VPreset.m_vertices[0].t = { 0.0f, 0.0f };
	m_VPreset.m_vertices[1].t = { 1.0f, 0.0f };
	m_VPreset.m_vertices[2].t = { 0.0f, 1.0f };
	m_VPreset.m_vertices[3].t = { 1.0f, 1.0f };
}

void MyBaseObject::setIndices()
{
	m_VPreset.m_indexes.push_back({ 0, 1, 2 });
	m_VPreset.m_indexes.push_back({ 2, 1, 3 });
}

HRESULT MyBaseObject::createVertexBuf()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = m_VPreset.m_vertices.size() * sizeof(MyVertex);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VPreset.m_vertices.at(0);

	hr = I_DEVICE->CreateBuffer(&bd, &sd, m_VPreset.m_pVertexBuf.GetAddressOf());

	return hr;
}

HRESULT MyBaseObject::createIndexBuf()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = m_VPreset.m_indexes.size() * sizeof(MyTriangleIndexes);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VPreset.m_indexes.at(0);

	hr = I_DEVICE->CreateBuffer(&bd, &sd, m_VPreset.m_pIndexBuf.GetAddressOf());

	return hr;
}

bool MyBaseObject::create()
{
	HRESULT hr = S_OK;

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyBaseObject::create(wstring wszShaderFileName, wstring wszTextureFileName)
{
	HRESULT hr = S_OK;

	if (!setShader(wszShaderFileName)) { return false; }

	if (!setTexture(wszTextureFileName)) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
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
	preRender();

	postRender();
	return true;
}

bool MyBaseObject::release()
{
	return true;
}

void MyBaseObject::setColors(MyVector4F color)
{
	for (int i = 0; i < 4; i++) { m_VPreset.m_vertices[i].c = color; }
}

bool MyBaseObject::preRender()
{
	m_VPreset.m_pShader->render();	//쉐이더와 레이아웃 세팅
	m_VPreset.m_pTexture->render();	//PS쉐이더에 텍스처 세팅

	I_DCONTEXT->IASetVertexBuffers(0, 1,
		m_VPreset.m_pVertexBuf.GetAddressOf(), &m_VPreset.m_stride,
		&m_VPreset.m_offset);
	I_DCONTEXT->IASetIndexBuffer(m_VPreset.m_pIndexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);
	I_DCONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

bool MyBaseObject::postRender()
{
	//Draw는 인덱스 버퍼가 정의되어 있지 않은 경우 사용
	if (!m_VPreset.m_pIndexBuf.Get())
	{
		I_DCONTEXT->Draw(m_VPreset.m_vertices.size(), 0);
	}
	//DrawIndexed는 인덱스 버퍼가 정의 되어 있는 경우 사용
	I_DCONTEXT->DrawIndexed(m_VPreset.m_indexes.size() * sizeof(MyTriangleIndexes) / sizeof(UINT), 0, 0);
	return true;
}

bool MyBaseObject::setShader(wstring wszShaderFileName)
{
	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	return true;
}

bool MyBaseObject::setTexture(wstring wszTextureFileName)
{
	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	return true;
}

bool MyBaseObject::setTexture(MyTexture* pTexture)
{
	if (pTexture) { m_VPreset.m_pTexture = pTexture; return true; }
	return false;
}

bool MyBaseObject::updateVertexBuffer()
{
	I_DCONTEXT->UpdateSubresource(m_VPreset.m_pVertexBuf.Get(),
		0,
		nullptr,
		&m_VPreset.m_vertices.at(0),
		0, 0);
	return true;
}

