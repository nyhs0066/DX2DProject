#include "myeffect.h"

MyEffect::MyEffect()
{
    m_pSprite = nullptr;

    m_fLifeSpanT = 0.0f;
    m_fElapseT = 0.0f;
    m_fplayT = 0.0f;
    m_fStepT = 0.0f;

    m_fTimer = 0.0f;
    m_iCuridx = 0;
}

MyEffect::~MyEffect()
{
    m_pSprite = nullptr;
}

bool MyEffect::loadSprite(wstring wszSpriteName)
{
    m_pSprite = GET_ST_SPRITE(wszSpriteName);
    if (!m_pSprite) { return false; }

    setTexRect(m_pSprite->m_spriteArray[0]);
    
    return true;
}

bool MyEffect::init()
{
    if (m_pSprite)
    {
        m_fLifeSpanT = 1.0f * m_pSprite->m_spriteArray.size();
        m_fplayT = m_fLifeSpanT;
        m_fStepT = m_fplayT / m_pSprite->m_spriteArray.size();
    }

    return true;
}

bool MyEffect::frame()
{
    m_fElapseT += MAINTIMER.getOneFrameTimeF();
    m_fTimer += MAINTIMER.getOneFrameTimeF();

    if (m_fStepT <= m_fTimer)
    {
        m_iCuridx++;
        m_fTimer -= m_fStepT;

        if (m_iCuridx >= m_pSprite->m_spriteArray.size()) { m_iCuridx = 0; }

        setTexRect(m_pSprite->m_spriteArray[m_iCuridx]);
    }

    if (m_fElapseT >= m_fLifeSpanT) { return false; }

    return true;
}
