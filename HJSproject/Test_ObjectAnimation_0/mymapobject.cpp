#include "mymapobject.h"

void MyMapObject::setVertices()
{
	for (int i = 0; i < 4; i++) { m_VPreset.m_vertices.push_back(MyVertex()); };

	m_VPreset.m_vertices[0].p = { -1.0f, 1.0f, 0.0f };
	m_VPreset.m_vertices[1].p = { 1.0f, 1.0f, 0.0f };
	m_VPreset.m_vertices[2].p = { -1.0f, -1.0f, 0.0f };
	m_VPreset.m_vertices[3].p = { 1.0f, -1.0f, 0.0f };

	m_VPreset.m_vertices[0].t = { 0.0f, 0.0f };
	m_VPreset.m_vertices[1].t = { 1.0f, 0.0f };
	m_VPreset.m_vertices[2].t = { 0.0f, 1.0f };
	m_VPreset.m_vertices[3].t = { 1.0f, 1.0f };
}

void MyMapObject::setIndices()
{
	m_VPreset.m_indexes.push_back({ 0, 1, 2 });
	m_VPreset.m_indexes.push_back({ 2, 1, 3 });
}

void MyMapObject::setTexPos()
{
	FLOAT LTX = m_tRect.pos.x / m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT LTY = m_tRect.pos.y / m_VPreset.m_pTexture->m_TextureDesc.Height;
	FLOAT width = m_tRect.fWLH.v[0] / m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT height = m_tRect.fWLH.v[1] / m_VPreset.m_pTexture->m_TextureDesc.Height;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].t
				= { LTX + width * j, LTY + height * i };
		}
	}
}

MyMapObject::MyMapObject()
{

}

MyMapObject::~MyMapObject()
{
	release();
}

bool MyMapObject::create(wstring wszShaderFileName, wstring wszTextureFileName, 
	UINT stTexX, UINT stTexY, UINT texWidth, UINT texHeight)
{
	HRESULT hr = S_OK;

	m_tRect.pos.x = stTexX;
	m_tRect.pos.y = stTexY;
	m_tRect.fWLH.v[0] = texWidth;
	m_tRect.fWLH.v[1] = texHeight;

	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyMapObject::init()
{
	m_VPreset.m_stride = sizeof(MyVertex);
	m_VPreset.m_offset = 0;

	setTexPos();
	return true;
}

bool MyMapObject::frame()
{
	I_DCONTEXT->UpdateSubresource(m_VPreset.m_pVertexBuf,
		0,
		nullptr,
		&m_VPreset.m_vertices.at(0),
		0, 0);
	return true;
}

bool MyMapObject::render()
{
	preRender();

	I_DCONTEXT->IASetVertexBuffers(0, 1,
		&m_VPreset.m_pVertexBuf, &m_VPreset.m_stride,
		&m_VPreset.m_offset);
	I_DCONTEXT->IASetIndexBuffer(m_VPreset.m_pIndexBuf, DXGI_FORMAT_R32_UINT, 0);
	I_DCONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	postRender();
	return true;
}

bool MyMapObject::release()
{
	m_VPreset.release();

	return true;
}

void MyMapObject::setPosition(FLOAT stX, FLOAT stY)
{
	FLOAT LTX = ((m_posRect.pos.x / MyWindow::cWidth) * 2 - 1.0f);
	FLOAT LTY = -((m_posRect.pos.y / MyWindow::cHeight) * 2 - 1.0f);
	FLOAT width = (m_posRect.fWLH.v[0] / MyWindow::cWidth) * 2;
	FLOAT height = (m_posRect.fWLH.v[1] / MyWindow::cHeight) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { LTX + width * j, LTY + height * i, 0.0f };
		}
	}
}