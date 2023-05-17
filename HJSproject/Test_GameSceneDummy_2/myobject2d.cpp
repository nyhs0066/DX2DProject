#include "myobject2d.h"

MyObject2D::MyObject2D()
{
	m_fSpeed = 0.0f;
	m_fMass = 0.0f;
	m_fAngle = 0.0f;
	m_fAttackTimer = 0.0f;
	m_pMaskTexture = nullptr;

	ZeroMemory(&m_SPRect, sizeof(MyExRect));
	ZeroMemory(&m_TRect, sizeof(MyExRect));
}

MyObject2D::~MyObject2D()
{
	release();
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName, MyExRect pRect, MyExRect bRect)
{
	HRESULT hr = S_OK;

	m_VPreset.m_pShader = LOAD_SHADER(wszShaderFileName);
	if (!m_VPreset.m_pShader) { return false; }

	m_VPreset.m_pTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!m_VPreset.m_pTexture) { return false; }

	m_TRect = { 0.0f, 0.0f,
		(FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Width, (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Height };

	if (!m_VPreset.m_pVertexBuf)
	{
		hr = createVertexBuf();
		if (FAILED(hr)) { return false; }

		hr = createIndexBuf();
		if (FAILED(hr)) { return false; }
	}

	m_BRect = bRect;

	setPosRect(pRect);
	setTexRect(m_TRect);
	return true;
}

bool MyObject2D::create(wstring wszShaderFileName, wstring wszTextureFileName,
	wstring wszMaskFileName, MyExRect pRect,  MyExRect bRect)
{
	m_pMaskTexture = LOAD_TEXTURE(wszMaskFileName);
	if (!m_pMaskTexture) { return false; }

	if (!create(wszShaderFileName, wszTextureFileName, pRect, bRect)) { return false; }

	return false;
}

bool MyObject2D::postFrame(const MyExRect& camRt, FLOAT radian)
{
	setPosRect(m_SPRect);
	adjustCRect(m_SPRect);

	MyExRect rt = m_CSRect;

	ScreenToView(rt, camRt);

	m_DRect.set((rt.pos.x / camRt.fWH.v[0]) * 2,
		-(rt.pos.y / camRt.fWH.v[1]) * 2,
		(rt.fWH.v[0] / camRt.fWH.v[0]) * 2,
		-(rt.fWH.v[1] / camRt.fWH.v[1]) * 2
	);

	texRotation(radian);
	updateVertexBuffer();

	return true;
}

bool MyObject2D::postFrame(FLOAT radian)
{
	setPosRect(m_SPRect);

	m_DRect.set((m_SPRect.pos.x / MyWindow::cWidth) * 2 - 1.0f,
		-((m_SPRect.pos.y / MyWindow::cHeight) * 2 - 1.0f),
		(m_SPRect.fWH.v[0] / MyWindow::cWidth) * 2,
		-(m_SPRect.fWH.v[1] / MyWindow::cHeight) * 2
	);

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

void MyObject2D::ScreenToView(MyExRect& rt, const MyExRect& camRt)
{
	rt.pos.x -= camRt.pos.x;
	rt.pos.y -= camRt.pos.y;
}

void MyObject2D::setPosRect(MyExRect rt)
{
	m_SPRect = rt;
}

void MyObject2D::setTexRect(MyExRect rt)
{
	m_TRect = rt;

	FLOAT pX = (1.0f / m_VPreset.m_pTexture->m_TextureDesc.Width) * 0.49f;
	FLOAT pY = (1.0f / m_VPreset.m_pTexture->m_TextureDesc.Height) * 0.49f;

	m_DTexRect.set(rt.pos.x / m_VPreset.m_pTexture->m_TextureDesc.Width + pX,
		rt.pos.y / m_VPreset.m_pTexture->m_TextureDesc.Height + pY,
		rt.fWH.v[0] / m_VPreset.m_pTexture->m_TextureDesc.Width,
		rt.fWH.v[1] / m_VPreset.m_pTexture->m_TextureDesc.Height
	);
}

void MyObject2D::setBoundRect(MyExRect rt)
{
	m_BRect = rt;
}

bool MyObject2D::boundaryCheck()
{
	return true;;
}

MyVector2F MyObject2D::staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyObject2D::dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyVector2F MyObject2D::dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt)
{
	return MyVector2F();
}

MyExRect MyObject2D::getCSRect() const
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

	offX = (m_DRect.pt[0].x + m_DRect.pt[1].x) * 0.5f;
	offY = (m_DRect.pt[0].y + m_DRect.pt[2].y) * 0.5f;

	for (int i = 0; i < 4; i++)
	{
		tX = m_DRect.pt[i].x - offX;
		tY = m_DRect.pt[i].y - offY;

		m_DRect.pt[i].x = cosf(radian) * tX - sinf(radian) * tY + offX;
		m_DRect.pt[i].y = sinf(radian) * tX + cosf(radian) * tY + offY;
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

void MyObject2D::adjustCRect(MyExRect& rt)
{
	m_CSRect.set(	rt.pos.x - rt.fWH.v[0] * 0.5f,
					rt.pos.y - rt.fWH.v[1] * 0.5f,
					rt.fWH.x,
					rt.fWH.y);
}

bool MyObject2D::updateVertexBuffer()
{
	for (int i = 0; i < 4; i++)
	{
		m_VPreset.m_vertices[i].p = { m_DRect.pt[i].x, m_DRect.pt[i].y, 0.0f };
	}

	for (int i = 0; i < 4; i++)
	{
		m_VPreset.m_vertices[i].t = m_DTexRect.pt[i];
	}

	I_DCONTEXT->UpdateSubresource(m_VPreset.m_pVertexBuf.Get(),
		0,
		nullptr,
		&m_VPreset.m_vertices.at(0),
		0, 0);

	return true;
}

MyVector2F MyObject2D::getForce()
{
	return m_vForce;
}

HPBar::HPBar()
{
	pTarget = nullptr;
}

HPBar::~HPBar()
{
	release();
}

bool HPBar::create(wstring wszShaderFileName, MyObject2D* pTarget)
{
	MyObject2D::create(wszShaderFileName, L"../../data/background/red.png");
	this->pTarget = pTarget;

	BarFrame.create(wszShaderFileName, L"../../data/shapes/HollowSquare.png");
	BarFrame.setPosRect({ pTarget->m_SPRect.pos.x, pTarget->m_SPRect.pos.y - pTarget->m_SPRect.fWH.y * 0.75f, pTarget->m_SPRect.fWH.x,  pTarget->m_SPRect.fWH.y * 0.2f });

	setPosRect({ pTarget->m_SPRect.pos.x, pTarget->m_SPRect.pos.y - pTarget->m_SPRect.fWH.y * 0.6f, BarFrame.m_SPRect.fWH.x,  BarFrame.m_SPRect.fWH.y * 0.9f });

	return true;
}

bool HPBar::setTarget(MyObject2D* pTarget)
{
	return this->pTarget = pTarget;
}

bool HPBar::init()
{
	return true;
}

bool HPBar::postFrame(const MyExRect& camRt, FLOAT radian)
{
	BarFrame.setPosRect({ pTarget->m_SPRect.pos.x, pTarget->m_SPRect.pos.y - pTarget->m_SPRect.fWH.y * 0.75f, pTarget->m_SPRect.fWH.x,  pTarget->m_SPRect.fWH.y * 0.2f });

	FLOAT ratio = (FLOAT)pTarget->m_iCurHitPoint / pTarget->m_iMaxHitPoint;
	if (ratio < 0.0f) { ratio = 0.0f; }
	setPosRect({ pTarget->m_SPRect.pos.x, pTarget->m_SPRect.pos.y - pTarget->m_SPRect.fWH.y * 0.75f, (BarFrame.m_SPRect.fWH.x)* ratio,  BarFrame.m_SPRect.fWH.y * 0.9f });

	MyObject2D::postFrame(camRt);
	BarFrame.postFrame(camRt);

	return true;
}

bool HPBar::render()
{
	BarFrame.render();
	MyObject2D::render();
	return true;
}

bool HPBar::release()
{
	pTarget = nullptr;
	BarFrame.release();
	return true;
}
