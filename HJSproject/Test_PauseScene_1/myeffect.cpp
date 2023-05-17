#include "myeffect.h"

std::unique_ptr<MyObject2D> MyEffect::g_pDrawObj = nullptr;

MyEffect::MyEffect()
{
    if (!g_pDrawObj.get()) 
    { 
        g_pDrawObj = std::make_unique<MyObject2D>();
        g_pDrawObj->MyBaseObject::create();
    }
    m_pSprite = nullptr;
    m_pMaskTexture = nullptr;

    m_fLifeSpanT = 0.0f;
    m_fplayT = 0.0f;
    m_fStepT = 0.0f;

    m_fTimer = 0.0f;
    m_fElapseT = 0.0f;
    m_iCuridx = 0;
    m_LifeFlag = true;

    m_iDamage = 1;
    m_fSpeed = 0.0f;
    m_fRotateAnglePerSec = 0.0f;

    m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

MyEffect::~MyEffect()
{
    release();
}

bool MyEffect::create(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName)
{
    m_wszShaderName = wszShaderName;
    m_wszTexName = wszTexName;

    m_pSprite = GET_SPRITE(wszSpriteName);
    if (!m_pSprite) { return false; }

    if (m_pSprite->m_rtSpriteArray.size())
    {
        m_TRect = m_pSprite->m_rtSpriteArray[0];
    }
    else
    {
        m_TRect = m_pSprite->m_texSpriteArray[0]->m_TRect;
    }
    
    return true;
}

bool MyEffect::create(wstring wszShaderName, wstring wszTexName, wstring wszMaskName, wstring wszSpriteName)
{
    m_pMaskTexture = LOAD_TEXTURE(wszMaskName);
    if (!m_pMaskTexture) { return false; }

    if (!create(wszShaderName, wszTexName, wszSpriteName)) { return false; }

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

        if (m_pSprite->m_rtSpriteArray.size())
        {
            if (m_iCuridx >= m_pSprite->m_rtSpriteArray.size()) { m_iCuridx = 0; }
            m_TRect = m_pSprite->m_rtSpriteArray[m_iCuridx];
        }
        else
        {
            if (m_iCuridx >= m_pSprite->m_texSpriteArray.size()) { m_iCuridx = 0; }
            m_TRect = m_pSprite->m_texSpriteArray[m_iCuridx]->m_TRect;
        }
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

    if (m_pSprite->m_rtSpriteArray.size())
    {
        m_fStepT = fPlayT / m_pSprite->m_rtSpriteArray.size();
    }
    else
    {
        m_fStepT = fPlayT / m_pSprite->m_texSpriteArray.size();
    }
}

void MyEffect::setDirectionAndSpeed(MyVector2F vDirection, FLOAT fSpeed, FLOAT fRotateSpeed)
{
    m_vDirection = vDirection;
    m_fSpeed = fSpeed;
    m_fRotateAnglePerSec = fRotateSpeed;
}

bool MyEffect::preRender(const MyRect& camRt)
{
    g_pDrawObj->setShader(m_wszShaderName);
    g_pDrawObj->setTexture(m_wszTexName);
    
    if (m_pMaskTexture)
    {
        I_DCONTEXT->PSSetShaderResources(1, 1, &m_pMaskTexture->m_pSRView);
    }

    g_pDrawObj->setColors(m_color);
    g_pDrawObj->setTexRect(m_TRect);
    g_pDrawObj->setPosRect(m_SPRect);
    g_pDrawObj->postFrame(camRt);

    return true;
}

bool MyEffect::release()
{
    m_pSprite = nullptr;

    m_pCreateEPresets.clear();
    m_pDestructEPresets.clear();
    m_pEventEPresets.clear();
    return false;
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

        if (m_pSprite->m_rtSpriteArray.size())
        {
            if (m_iCuridx >= m_pSprite->m_rtSpriteArray.size()) { m_iCuridx = 0; }
            m_TRect = m_pSprite->m_rtSpriteArray[m_iCuridx];
        }
        else
        {
            if (m_iCuridx >= m_pSprite->m_texSpriteArray.size()) { m_iCuridx = 0; }
            m_TRect = m_pSprite->m_texSpriteArray[m_iCuridx]->m_TRect;
        }
    }

    m_SPRect.pos += m_vDirection * m_fSpeed * oneFT;
    setPosRect(m_SPRect);

    if (m_fElapseT >= m_fLifeSpanT) { m_LifeFlag = false; }

    return true;
}