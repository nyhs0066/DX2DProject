#include "myeffect.h"

MyEffectPreset::MyEffectPreset()
{
    m_pSprite = nullptr;
    m_pDrawing = new MyObject2D;
}

MyEffectPreset::~MyEffectPreset()
{
    m_pSprite = nullptr;
    if (m_pDrawing) { delete m_pDrawing; m_pDrawing = nullptr; }
}

bool MyEffectPreset::createEffectPreset(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName)
{
    if (!m_pDrawing->create(wszShaderName, wszTexName)) { return false; }
    m_pSprite = GET_ST_SPRITE(wszSpriteName);

    if (!m_pSprite)
    {
        delete m_pDrawing;
        m_pDrawing = nullptr;
    }
    return true;
}

bool MyEffectPreset::createEffectPreset(wstring wszShaderName, wstring wszTexName, wstring wszMaskName, wstring wszSpriteName)
{
    if (m_pDrawing->create(wszShaderName, wszTexName, wszMaskName)) { return false; }
    m_pSprite = GET_ST_SPRITE(wszSpriteName);

    if (!m_pSprite)
    {
        delete m_pDrawing;
        m_pDrawing = nullptr;
    }
    return true;
}

MyEffect::MyEffect()
{
    m_pEPreset = nullptr;

    m_fLifeSpanT = 0.0f;
    m_fplayT = 0.0f;
    m_fStepT = 0.0f;

    m_fElapseT = 0.0f;
    m_fTimer = 0.0f;
    m_iCuridx = 0;
}

MyEffect::~MyEffect()
{
    m_pEPreset = nullptr;
}

bool MyEffect::init()
{
    m_SPRect.fWH = m_pEPreset->m_pDrawing->getPosRect().fWH;
    m_CSRect = m_pEPreset->m_pDrawing->getCollisionRect();

    return true;
}

bool MyEffect::update()
{
    m_fElapseT += MAINTIMER.getOneFrameTimeF();
    m_fTimer += MAINTIMER.getOneFrameTimeF();

    if (m_fStepT <= m_fTimer)
    {
        m_iCuridx++;
        m_fTimer -= m_fStepT;

        if (m_iCuridx >= m_pEPreset->m_pSprite->m_spriteArray.size()) { m_iCuridx = 0; }

        m_TRect = m_pEPreset->m_pSprite->m_spriteArray[m_iCuridx];
    }

    if (m_fElapseT >= m_fLifeSpanT) { return false; }

    return true;
}

void MyEffect::setPosition(MyVector2F pos)
{
    m_SPRect.pos = pos;
}

void MyEffect::setTimeProperty(FLOAT fLifeSpanT, FLOAT fPlayT)
{
    m_fLifeSpanT = fLifeSpanT;
    m_fplayT = fPlayT;
    m_fStepT = fPlayT / m_pEPreset->m_pSprite->m_spriteArray.size();
}

bool MyEffect::preRender(const MyRect& camRt)
{
    m_pEPreset->m_pDrawing->setTexRect(m_TRect);
    m_pEPreset->m_pDrawing->setPosRect(m_SPRect);
    m_pEPreset->m_pDrawing->postFrame(camRt);

    return true;
}
