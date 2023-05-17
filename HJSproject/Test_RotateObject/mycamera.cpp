#include "mycamera.h"

MyCamera::MyCamera()
{
    ZeroMemory(&m_Camera, sizeof(MyRect));
}

MyCamera::~MyCamera()
{
    release();
}

bool MyCamera::init()
{
    return true;
}

bool MyCamera::frame()
{
    if (MAININPUT.getKeyState(VK_ADD) == KEY_DOWN) { zoom(1.2f); }
    if (MAININPUT.getKeyState(VK_SUBTRACT) == KEY_DOWN) { zoom(0.8f); }

    if (m_pFollowing)
    {
        //이미 좌표가 중앙에 와있다.
        MyRect fRect = m_pFollowing->getPosRect();

        m_Camera.pos = fRect.pos;

        if (m_Camera.pos.x < m_bRect.pos.x + m_Camera.fWH.v[0] * 0.5f)
        {
            m_Camera.pos.x = m_bRect.pos.x + m_Camera.fWH.v[0] * 0.5f;
            if (m_Camera.pos.x > m_bRect.pos.x + m_bRect.fWH.v[0] - m_Camera.fWH.v[0] * 0.5f)
            {
                m_Camera.pos.x = m_bRect.pos.x + m_bRect.fWH.v[0] * 0.5f;
            }
        }
        else if (m_Camera.pos.x > m_bRect.pos.x + m_bRect.fWH.v[0] - m_Camera.fWH.v[0] * 0.5f)
        {
            m_Camera.pos.x = m_bRect.pos.x + m_bRect.fWH.v[0] - m_Camera.fWH.v[0] * 0.5f;
            if (m_Camera.pos.x < m_bRect.pos.x + m_Camera.fWH.v[0] * 0.5f)
            {
                m_Camera.pos.x = m_bRect.pos.x + m_bRect.fWH.v[0] * 0.5f;
            }
        }

        if (m_Camera.pos.y < m_bRect.pos.y + m_Camera.fWH.v[1] * 0.5f)
        {
            m_Camera.pos.y = m_bRect.pos.y + m_Camera.fWH.v[1] * 0.5f;
            if (m_Camera.pos.y > m_bRect.pos.y + m_bRect.fWH.v[1] - m_Camera.fWH.v[1] * 0.5f)
            {
                m_Camera.pos.y = m_bRect.pos.y + m_bRect.fWH.v[1] * 0.5f;
            }
        }
        else if (m_Camera.pos.y > m_bRect.pos.y + m_bRect.fWH.v[1] - m_Camera.fWH.v[1] * 0.5f)
        {
            m_Camera.pos.y = m_bRect.pos.y + m_bRect.fWH.v[1] - m_Camera.fWH.v[1] * 0.5f;
            if (m_Camera.pos.y < m_bRect.pos.y + m_Camera.fWH.v[1] * 0.5f)
            {
                m_Camera.pos.y = m_bRect.pos.y + m_bRect.fWH.v[1] * 0.5f;
            }
        }
    }

    return true;
}

bool MyCamera::render()
{
    return true;
}

bool MyCamera::release()
{
    m_pFollowing = nullptr;

    return true;
}

void MyCamera::setFollowTarget(MyObject2D* pObj)
{
    m_pFollowing = pObj;
}

void MyCamera::setBoundaryRect(const MyRect& bRect)
{
    m_bRect = bRect;
}

void MyCamera::setCamPos(const MyVector2F& pos)
{
    m_Camera.pos = pos;
}

void MyCamera::setCamArea(const MyVector2F& fWH)
{
    m_Camera.fWH = fWH;
}

void MyCamera::setCamRect(const MyRect& rt)
{
    m_Camera = rt;
}

MyVector2F MyCamera::getCamPos() const
{
    return m_Camera.pos;
}

MyVector2F MyCamera::getCamArea() const
{
    return m_Camera.fWH;
}

MyRect MyCamera::getCamRect() const
{
    return m_Camera;
}

void MyCamera::zoom(FLOAT magnification)
{
    m_Camera.fWH = m_Camera.fWH * magnification;
}
