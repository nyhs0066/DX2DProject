#include "mydynamicobject.h"

std::random_device g_rd;
std::default_random_engine gen(g_rd());
std::uniform_real_distribution<float> g_floatDist(-10.0f, 10.0f);

MyDynamicObject2D::MyDynamicObject2D()
{
	m_fSpeed = 0.0f;
}

MyDynamicObject2D::~MyDynamicObject2D()
{
	release();
}

bool MyDynamicObject2D::init()
{
	MyBaseObject::init();

	m_vDirection.x = g_floatDist(gen);
	m_vDirection.y = g_floatDist(gen);
	m_vDirection.normalization();

	m_fSpeed = 700.0f;
	return true;
}

bool MyDynamicObject2D::frame()
{
	m_pRect.pos += m_vDirection * m_fSpeed * MAINTIMER.getOneFrameTimeF();

	if (m_pRect.pos.x < 24.0f)
	{
		m_pRect.pos.x = 24.0f;
		m_vDirection.x = -m_vDirection.x;
	}

	if (m_pRect.pos.x > MyWindow::cWidth - 24.0f - m_pRect.fWH.v[0])
	{
		m_pRect.pos.x = MyWindow::cWidth - 24.0f - m_pRect.fWH.v[0];
		m_vDirection.x = -m_vDirection.x;
	}

	if (m_pRect.pos.y < 24.0f)
	{
		m_pRect.pos.y = 24.0f;
		m_vDirection.y = -m_vDirection.y;
	}

	if (m_pRect.pos.y > MyWindow::cHeight - m_pRect.fWH.v[1])
	{
		m_pRect.pos.y = MyWindow::cHeight - m_pRect.fWH.v[1];
		m_vDirection.y = -m_vDirection.y;
	}

	setPosRect(m_pRect);

	I_DCONTEXT->UpdateSubresource(m_VPreset.m_pVertexBuf,
		0,
		nullptr,
		&m_VPreset.m_vertices.at(0),
		0, 0);
	return true;
}