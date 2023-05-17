#include "mybackgroundobject.h"

MyBackGroundObject::MyBackGroundObject()
{

}

MyBackGroundObject::~MyBackGroundObject()
{

}

void MyBackGroundObject::setBGdefault()
{
	//2400 * 1600
	FLOAT tw = (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT th = (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Height;

	m_SPRect.rt = { tw * 0.75f, th, tw * 1.5f, th * 2 };
	m_TRect.rt = { 0.0f, 0.0f, tw * 1.5f, th * 2 };

	setPosRect(m_SPRect);
	setTexRect(m_TRect);
}
