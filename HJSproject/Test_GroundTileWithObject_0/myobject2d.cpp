#include "myobject2d.h"

MyObject2D::MyObject2D()
{
	m_fSpeed = 0.0f;
	m_fMass = 0.0f;

	ZeroMemory(&m_pRect, sizeof(MyRect));
	ZeroMemory(&m_tRect, sizeof(MyRect));
}

MyObject2D::~MyObject2D()
{
	release();
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName,
	wstring wszMaskFileName, MyRect& pRect, MyRect& tRect, MyRect& bRect)
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

	m_boundary = bRect;

	setPosRect(pRect);
	setTexRect(tRect);

	return true;
}

void MyObject2D::setPosRect(MyRect& rt)
{
	m_pRect = rt;

	FLOAT LTX = ((m_pRect.pos.x / m_boundary.fWH.v[0]) * 2 - 1.0f);
	FLOAT LTY = -((m_pRect.pos.y / m_boundary.fWH.v[1]) * 2 - 1.0f);
	FLOAT width = (m_pRect.fWH.v[0] / m_boundary.fWH.v[0]) * 2;
	FLOAT height = -(m_pRect.fWH.v[1] / m_boundary.fWH.v[1]) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { LTX + width * j, LTY + height * i, 0.0f };
		}
	}

	updateVertexBuffer();
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

	updateVertexBuffer();
}

MyRect& MyObject2D::getPosRect()
{
	return m_pRect;
}

MyRect& MyObject2D::getTexRect()
{
	return m_tRect;
}

MyVector2F& MyObject2D::getDirection()
{
	return m_vDirection;
}

void MyObject2D::setDirection(MyVector2F& vDirection)
{
	m_vDirection = vDirection;
}

void MyObject2D::setForce(MyVector2F& vforce)
{
	m_vForce = vforce;
}

MyVector2F& MyObject2D::getForce()
{
	return m_vForce;
}

void MyObject2D::resetVector(MyVector2F& v)
{
	v = { 0.0f, 0.0f };
}
