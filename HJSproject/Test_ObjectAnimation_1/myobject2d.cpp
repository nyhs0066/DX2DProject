#include "myobject2d.h"

MyObject2D::MyObject2D()
{
	m_fSpeed = 0.0f;

	ZeroMemory(&m_pRect, sizeof(MyRect));
	ZeroMemory(&m_tRect, sizeof(MyRect));
}

MyObject2D::~MyObject2D()
{
	release();
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName,
	wstring wszMaskFileName, MyRect& pRect, MyRect& tRect)
{
	HRESULT hr = S_OK;

	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	setPosRect(pRect);
	setTexRect(tRect);

	return true;
}

bool MyObject2D::frame()
{
	updateVertexBuffer();
	return true;
}

bool MyObject2D::render()
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

void MyObject2D::setPosRect(MyRect& rt)
{
	m_pRect = rt;

	FLOAT LTX = ((m_pRect.pos.x / MyWindow::cWidth) * 2 - 1.0f);
	FLOAT LTY = -((m_pRect.pos.y / MyWindow::cHeight) * 2 - 1.0f);
	FLOAT width = (m_pRect.fWH.v[0] / MyWindow::cWidth) * 2;
	FLOAT height = -(m_pRect.fWH.v[1] / MyWindow::cHeight) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { LTX + width * j, LTY + height * i, 0.0f };
		}
	}
}

void MyObject2D::setTexRect(MyRect& rt)
{
	m_tRect = rt;

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

MyRect& MyObject2D::getPosRect()
{
	return m_pRect;
}

MyRect& MyObject2D::getTexRect()
{
	return m_tRect;
}

MyVector2F MyObject2D::getDirection()
{
	return m_vDirection;
}

bool MyObject2D::setDirection(MyVector2F vDirection)
{
	m_vDirection = vDirection;
	return true;
}
