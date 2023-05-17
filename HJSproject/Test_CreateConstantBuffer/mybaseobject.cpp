#include "mybaseobject.h"

MyBaseObject::MyBaseObject()
{
	m_pVertexBuf = nullptr;
	m_pShader = nullptr;

	setVertices();
}

MyBaseObject::~MyBaseObject()
{
	release();
}

void MyBaseObject::setVertices()
{
	//���� ��ǥ : NDC(Normalized Device Coordinate)
	//���� ���� : (R32 G32 B32 A32) FLOAT
	//�ؼ� ��ǥ : NSC(Normalized Screen Coordinate)

	//���� ���۸� ���� ��(���� ���� 3�������� ������ �ﰢ�� 2���� ���̴� ����)
	/*m_vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f} });
	m_vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, {10.0f, 0.0f} });
	m_vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, {0.0f, 10.0f} });
	m_vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, {0.0f, 10.0f} });
	m_vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, {10.0f, 0.0f} });
	m_vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, {10.0f, 10.0f} });*/

	//���� ���ۿ� �ε��� ���� �� �� ���� ��
	m_vertices.push_back({ { -0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f} });
	m_vertices.push_back({ { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, {1.0f, 0.0f} });
	m_vertices.push_back({ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, {0.0f, 1.0f} });
	m_vertices.push_back({ { 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, {1.0f, 1.0f} });

	m_indexes.push_back({ 0, 1, 2 });
	m_indexes.push_back({ 2, 1, 3 });
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

HRESULT MyBaseObject::createIndexBuf()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = m_indexes.size() * sizeof(MyTriangleIndexes);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_indexes.at(0);

	hr = I_DEVICE->CreateBuffer(&bd, &sd, &m_pIndexBuf);

	return hr;
}

HRESULT MyBaseObject::createConstBuf()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(MyConstantBufferData);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	hr = I_DEVICE->CreateBuffer(&bd, nullptr, &m_pConstBuf);

	return hr;
}

bool MyBaseObject::create(wstring wszShaderFileName, wstring wszTextureFileName)
{
	HRESULT hr = S_OK;

	m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_pShader) { return false; }

	m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_pTexture) { return false; }

	hr = m_SState.create();
	if (FAILED(hr)) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	hr = createConstBuf();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyBaseObject::init()
{
	return true;
}

bool MyBaseObject::frame()
{
	float fTime = MAINTIMER.getRunningTimeF();
	float cycle = sinf(fTime) * 0.5f + 0.5f;

	//������� ������Ʈ ��
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	I_DCONTEXT->Map(m_pConstBuf, 0, D3D11_MAP_WRITE_DISCARD,0, &mappedResource);
	MyConstantBufferData* pConstData = reinterpret_cast<MyConstantBufferData*>(mappedResource.pData);
	pConstData->vColor = { sinf(fTime) * 0.5f + 0.5f, cosf(fTime) * 0.5f + 0.5f, sinf(-fTime) * 0.5f + 0.5f, 1.0f };
	pConstData->fTime = cycle;
	I_DCONTEXT->Unmap(m_pConstBuf, 0);
	return true;
}

bool MyBaseObject::render()
{
	UINT strides = sizeof(MyVertex);
	UINT offset = 0;
	m_pShader->render();	//���̴��� ���̾ƿ� ����
	m_pTexture->render();	//���̴��� �ؽ�ó ����

	I_DCONTEXT->IASetVertexBuffers(0, 1, &m_pVertexBuf, &strides, &offset);
	I_DCONTEXT->IASetIndexBuffer(m_pIndexBuf, DXGI_FORMAT_R32_UINT, 0);
	I_DCONTEXT->VSSetConstantBuffers(0, 1, &m_pConstBuf);
	I_DCONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	I_DCONTEXT->PSSetSamplers(0, 1, &m_SState.m_pSState);

	//Draw�� �ε��� ���۰� ���ǵǾ� ���� ���� ��� ���
	// I_DCONTEXT->Draw(m_vertices.size(), 0);
	//DrawIndexed�� �ε��� ���۰� ���� �Ǿ� �ִ� ��� ���
	I_DCONTEXT->DrawIndexed(m_indexes.size()*sizeof(MyTriangleIndexes)/sizeof(UINT), 0, 0);

	return true;
}

bool MyBaseObject::release()
{
	if (m_pIndexBuf) { m_pIndexBuf->Release(); m_pIndexBuf = nullptr; }
	if (m_pVertexBuf) { m_pVertexBuf->Release(); m_pVertexBuf = nullptr; }
	if (m_pConstBuf) { m_pConstBuf->Release(); m_pConstBuf = nullptr; }

	m_pShader = nullptr;
	m_pTexture = nullptr;
	m_SState.release();

	m_vertices.clear();
	m_indexes.clear();
	
	return true;
}