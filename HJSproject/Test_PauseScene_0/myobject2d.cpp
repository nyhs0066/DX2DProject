#include "myobject2d.h"

MyObject2D::MyObject2D()
{
	m_fSpeed = 0.0f;
	m_fMass = 0.0f;
	m_fAngle = 0.0f;
	m_pMaskTexture = nullptr;

	ZeroMemory(&m_SPRect, sizeof(MyRect));
	ZeroMemory(&m_TRect, sizeof(MyRect));
}

MyObject2D::~MyObject2D()
{
	release();
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName, MyRect pRect, MyRect bRect)
{
	HRESULT hr = S_OK;

	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	m_TRect = { 0.0f, 0.0f,
		(FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Width, (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Height };

	hr = createVertexBuf();
	if (FAILED(hr)) { return false; }

	hr = createIndexBuf();
	if (FAILED(hr)) { return false; }

	m_BRect = bRect;

	setPosRect(pRect);
	return true;
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName,
	wstring wszMaskFileName, MyRect pRect,  MyRect bRect)
{
	m_pMaskTexture = LOAD_TEXTURE(wszMaskFileName);
	if (!m_pMaskTexture) { return false; }

	if (!create(wszShaderFileName, wszTextureFileName, pRect, bRect)) { return false; }

	return false;
}

bool MyObject2D::postFrame(const MyRect& camRt, FLOAT radian)
{
	setPosRect(m_SPRect, camRt);
	texRotation(radian);
	updateVertexBuffer();

	return true;
}

bool MyObject2D::render()
{
	preRender();

	if (m_pMaskTexture)
	{
		I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);
	}

	postRender();
	return true;
}

bool MyObject2D::release()
{
	m_pMaskTexture = nullptr;
	return true;
}

void MyObject2D::ScreenToView(MyRect& rt, const MyRect& camRt)
{
	rt.pos.x -= camRt.pos.x;
	rt.pos.y -= camRt.pos.y;
}

void MyObject2D::setPosRect(MyRect rt)
{
	m_SPRect = rt;

	m_DRect.pos.x = (m_SPRect.pos.x / MyWindow::cWidth) * 2 - 1.0f;
	m_DRect.pos.y = -((m_SPRect.pos.y / MyWindow::cHeight) * 2 - 1.0f);
	m_DRect.fWH.v[0] = (m_SPRect.fWH.v[0] / MyWindow::cWidth) * 2;
	m_DRect.fWH.v[1] = (m_SPRect.fWH.v[1] / MyWindow::cHeight) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { m_DRect.pos.x + m_DRect.fWH.v[0] * j, m_DRect.pos.y - m_DRect.fWH.v[1] * i, 0.0f };
		}
	}

	updateVertexBuffer();
}

void MyObject2D::setPosRect(MyRect rt, const MyRect& camRt)
{
	m_SPRect = rt;

	m_CSRect.pos.x = rt.pos.x - rt.fWH.v[0] * 0.5f;
	m_CSRect.pos.y = rt.pos.y - rt.fWH.v[1] * 0.5f;
	m_CSRect.fWH = rt.fWH;

	rt = m_CSRect;

	ScreenToView(rt, camRt);

	m_DRect.pos.x = (rt.pos.x / camRt.fWH.v[0]) * 2;
	m_DRect.pos.y = -(rt.pos.y / camRt.fWH.v[1]) * 2;
	m_DRect.fWH.v[0] = (rt.fWH.v[0] / camRt.fWH.v[0]) * 2;
	m_DRect.fWH.v[1] = (rt.fWH.v[1] / camRt.fWH.v[1]) * 2;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_VPreset.m_vertices[i * 2 + j].p
				= { m_DRect.pos.x + m_DRect.fWH.v[0] * j, m_DRect.pos.y - m_DRect.fWH.v[1] * i, 0.0f };
		}
	}

	updateVertexBuffer();
}

void MyObject2D::setTexRect(MyRect rt)
{
	m_TRect = rt;

	FLOAT pX = (1.0f / m_VPreset.m_pTexture->m_TextureDesc.Width) * 0.49f;
	FLOAT pY = (1.0f / m_VPreset.m_pTexture->m_TextureDesc.Height) * 0.49f;

	FLOAT LTX = m_TRect.pos.x / m_VPreset.m_pTexture->m_TextureDesc.Width - pX;
	FLOAT LTY = m_TRect.pos.y / m_VPreset.m_pTexture->m_TextureDesc.Height - pY;
	FLOAT width = m_TRect.fWH.v[0] / m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT height = m_TRect.fWH.v[1] / m_VPreset.m_pTexture->m_TextureDesc.Height;

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

void MyObject2D::setBoundRect(MyRect rt)
{
	m_BRect = rt;
}

bool MyObject2D::boundaryCheck()
{
	return true;;
}

MyVector2F MyObject2D::staticCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyObject2D::dynamicCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt)
{
	return MyVector2F();
}

MyRect MyObject2D::getCSRect() const
{
	return m_CSRect;
}

MyVector2F MyObject2D::getDirection()
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

void MyObject2D::texRotation(FLOAT radian)
{
	FLOAT offX, offY;
	FLOAT tX, tY;

	offX = (m_VPreset.m_vertices[0].p.x + m_VPreset.m_vertices[1].p.x) * 0.5f;
	offY = (m_VPreset.m_vertices[0].p.y + m_VPreset.m_vertices[2].p.y) * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		tX = m_VPreset.m_vertices[i].p.x - offX;
		tY = m_VPreset.m_vertices[i].p.y - offY;

		m_VPreset.m_vertices[i].p.x = cosf(radian) * tX - sinf(radian) * tY + offX;
		m_VPreset.m_vertices[i].p.y = sinf(radian) * tX + cosf(radian) * tY + offY;
	}
}

void MyObject2D::arbitRotation(MyVector2F pivot, FLOAT radian)
{
	FLOAT tX, tY;

	tX = m_SPRect.pos.x - pivot.x;
	tY = m_SPRect.pos.y - pivot.y;

	m_SPRect.pos.x = cosf(radian) * tX + sinf(radian) * tY + pivot.x;
	m_SPRect.pos.y = -sinf(radian) * tX + cosf(radian) * tY + pivot.y;
}

MyVector2F MyObject2D::getForce()
{
	return m_vForce;
}