#include "myplayer.h"

void MyPlayer2F::setVertices()
{
	for (int i = 0; i < 4; i++) { m_VPreset.m_vertices.push_back(MyVertex()); };
}

void MyPlayer2F::setIndices()
{
	m_VPreset.m_indexes.push_back({ 0, 1, 2 });
	m_VPreset.m_indexes.push_back({ 2, 1, 3 });
}

void MyPlayer2F::setTexPos()
{
	FLOAT LTX = m_tRect.pos.x / m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT LTY = m_tRect.pos.y / m_VPreset.m_pTexture->m_TextureDesc.Height;
	FLOAT width = m_tRect.fWH.v[0] / m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT height = m_tRect.fWH.v[1] / m_VPreset.m_pTexture->m_TextureDesc.Height;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].t
				= { LTX + width * j, LTY + height * i };
		}
	}
}

MyPlayer2F::MyPlayer2F()
{
	m_pMaskTexture = nullptr;
	m_fSpeed = 0.0f;
}

MyPlayer2F::~MyPlayer2F()
{
	release();
}

bool MyPlayer2F::create(wstring wszShaderFileName, wstring wszTextureFileName,
	wstring wszMaskTextureFileName, MyRect posRect, MyRect texRect)
{
	HRESULT hr = S_OK;

	m_posRect.pos.x = posRect.pos.x;
	m_posRect.pos.y = posRect.pos.y;
	m_posRect.fWH.v[0] = posRect.fWH.x;
	m_posRect.fWH.v[1] = posRect.fWH.y;

	m_tRect.pos.x = texRect.pos.x;
	m_tRect.pos.y = texRect.pos.y;
	m_tRect.fWH.v[0] = texRect.fWH.v[0];
	m_tRect.fWH.v[1] = texRect.fWH.v[1];

	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	m_pMaskTexture = LOAD_TEXTURE(wszMaskTextureFileName);
	if (!m_pMaskTexture) { return false; }

	hr = m_VPreset.m_SState.create();
	if (FAILED(hr)) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyPlayer2F::init()
{
	m_VPreset.m_stride = sizeof(MyVertex);
	m_VPreset.m_offset = 0;
	m_fSpeed = 700.0f;

	setTexPos();
	setPosition(m_posRect.pos.x, m_posRect.pos.y);
	return true;
}

bool MyPlayer2F::frame()
{
	if (MAININPUT.getKeyState(VK_LEFT) != KEY_FREE) 
	{
		m_posRect.pos.x -= m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_posRect.pos.x < 24.0f) { m_posRect.pos.x = 24.0f; }
		setPosition(m_posRect.pos.x, m_posRect.pos.y);
	}

	if (MAININPUT.getKeyState(VK_RIGHT) != KEY_FREE)
	{
		m_posRect.pos.x += m_fSpeed * MAINTIMER.getOneFrameTimeF();

		if (m_posRect.pos.x > MyWindow::cWidth - 24.0f - m_posRect.fWH.v[0])
		{ 
			m_posRect.pos.x = MyWindow::cWidth - 24.0f - m_posRect.fWH.v[0];
		}
		setPosition(m_posRect.pos.x, m_posRect.pos.y);
	}

	I_DCONTEXT->UpdateSubresource(m_VPreset.m_pVertexBuf,
		0,
		nullptr,
		&m_VPreset.m_vertices.at(0),
		0, 0);
	return true;
}

bool MyPlayer2F::render()
{
	preRender();

	I_DCONTEXT->IASetVertexBuffers(0, 1,
		&m_VPreset.m_pVertexBuf, &m_VPreset.m_stride,
		&m_VPreset.m_offset);
	I_DCONTEXT->IASetIndexBuffer(m_VPreset.m_pIndexBuf, DXGI_FORMAT_R32_UINT, 0);
	I_DCONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);

	postRender();
	return true;
}

bool MyPlayer2F::release()
{
	m_VPreset.release();

	return true;
}

void MyPlayer2F::setPosition(FLOAT stX, FLOAT stY)
{
	m_posRect.pos.x = stX;
	m_posRect.pos.y = stY;

	FLOAT LTX = ((m_posRect.pos.x / MyWindow::cWidth) * 2 - 1.0f);
	FLOAT LTY = -((m_posRect.pos.y / MyWindow::cHeight) * 2 - 1.0f);
	FLOAT width = (m_posRect.fWH.v[0] / MyWindow::cWidth) * 2;
	FLOAT height = -(m_posRect.fWH.v[1] / MyWindow::cHeight) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { LTX + width * j, LTY + height * i, 0.0f };
		}
	}
}
