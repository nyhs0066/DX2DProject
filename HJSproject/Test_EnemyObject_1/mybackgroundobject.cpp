#include "mybackgroundobject.h"

MyBackGroundObject::MyBackGroundObject()
{

}

MyBackGroundObject::~MyBackGroundObject()
{

}

void MyBackGroundObject::setBGdefault()
{
	FLOAT tw = (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Width;
	FLOAT th = (FLOAT)m_VPreset.m_pTexture->m_TextureDesc.Height;

	m_SPRect.rt = { tw, th, tw*2, th*2 };
	m_TRect.rt = { 0.0f, 0.0f, tw*2, th*2 };

	setPosRect(m_SPRect);
	setTexRect(m_TRect);
}
