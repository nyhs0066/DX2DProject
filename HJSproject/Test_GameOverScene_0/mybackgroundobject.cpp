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

	m_SPRect.rt = { tw*0.5f, th*0.5f, tw, th };
	m_TRect.rt = { 0.0f, 0.0f, tw, th };

	setPosRect(m_SPRect);
	setTexRect(m_TRect);
}
