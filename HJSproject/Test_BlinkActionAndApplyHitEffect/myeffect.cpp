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

bool MyEffectPreset::create(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName)
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

bool MyEffectPreset::create(wstring wszShaderName, wstring wszTexName, wstring wszMaskName, wstring wszSpriteName)
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
    m_LifeFlag = true;

    m_fLifeSpanT = 0.0f;
    m_fplayT = 0.0f;
    m_fStepT = 0.0f;

    m_fElapseT = 0.0f;
    m_fTimer = 0.0f;
    m_iCuridx = 0;

    m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

MyEffect::~MyEffect()
{
    m_pEPreset = nullptr;
    m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
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

    if (m_fElapseT >= m_fLifeSpanT) { m_LifeFlag = false; }

    return true;
}

void MyEffect::setPosRect(MyRect posRt)
{
    m_SPRect = posRt;

    m_CSRect.pos = m_SPRect.pos - m_SPRect.fWH * 0.5f;
    m_CSRect.fWH = m_SPRect.fWH;
}

void MyEffect::setTimeProperty(FLOAT fLifeSpanT, FLOAT fPlayT)
{
    m_fLifeSpanT = fLifeSpanT;
    m_fplayT = fPlayT;
    m_fStepT = fPlayT / m_pEPreset->m_pSprite->m_spriteArray.size();
}

bool MyEffect::preRender(const MyRect& camRt)
{
    m_pEPreset->m_pDrawing->setColors(m_color);
    m_pEPreset->m_pDrawing->setTexRect(m_TRect);
    m_pEPreset->m_pDrawing->setPosRect(m_SPRect);
    m_pEPreset->m_pDrawing->postFrame(camRt);

    return true;
}

bool MyProjectile::update()
{
    FLOAT oneFT = MAINTIMER.getOneFrameTimeF();

    m_fElapseT += oneFT;
    m_fTimer += oneFT;

    if (m_fStepT <= m_fTimer)
    {
        m_iCuridx++;
        m_fTimer -= m_fStepT;

        if (m_iCuridx >= m_pEPreset->m_pSprite->m_spriteArray.size()) { m_iCuridx = 0; }

        m_TRect = m_pEPreset->m_pSprite->m_spriteArray[m_iCuridx];
    }

    m_SPRect.pos += m_direction * m_fSpeed * oneFT;
    setPosRect(m_SPRect);

    if (m_fElapseT >= m_fLifeSpanT) { m_LifeFlag = false; }

    return true;
}

bool MyProjectile::setProjectileProperty(MyEffectPreset* pPreset, MyRect posRt, FLOAT fLifeSpanT, FLOAT fPlayT, MyVector2F vDirection, FLOAT fspeed, UINT iDmg)
{
    m_pEPreset = pPreset;
    m_SPRect = posRt;
    m_TRect = m_pEPreset->m_pDrawing->getTexRect();

    setTimeProperty(fLifeSpanT, fPlayT);
    m_direction = vDirection;
    m_fSpeed = fspeed;
    m_iDamage = iDmg;

    return true;
}
