#include "tester.h"

bool TestCase::init()
{
	mapObj.create(L"../../data/shader/mydefaultshader.txt",
		L"../../data/subway.png",
		0, 0, 100, 100);
	mapObj.init();

	return true;
}

bool TestCase::frame()
{
	if (MAININPUT.getKeyState(VK_RIGHT) != KEY_FREE)
	{
		MyRect temp = mapObj.m_tRect;

		temp.pos.x += 100.0f * MAINTIMER.getOneFrameTimeF();

		if (temp.pos.x > mapObj.m_VPreset.m_pTexture->m_TextureDesc.Width - 100)
		{
			temp.pos.x = mapObj.m_VPreset.m_pTexture->m_TextureDesc.Width - 100;
		}

		mapObj.setTexPos(temp.pos.x, temp.pos.y);
	}
	if (MAININPUT.getKeyState(VK_LEFT) != KEY_FREE)
	{
		MyRect temp = mapObj.m_tRect;

		temp.pos.x -= 100.0f * MAINTIMER.getOneFrameTimeF();

		if (temp.pos.x < 0.0f)
		{
			temp.pos.x = 0.0f;
		}

		mapObj.setTexPos(temp.pos.x, temp.pos.y);
	}
	if (MAININPUT.getKeyState(VK_UP) != KEY_FREE)
	{
		MyRect temp = mapObj.m_tRect;

		temp.pos.y -= 100.0f * MAINTIMER.getOneFrameTimeF();

		if (temp.pos.y < 0.0f)
		{
			temp.pos.y = 0.0f;
		}

		mapObj.setTexPos(temp.pos.x, temp.pos.y);
	}
	if (MAININPUT.getKeyState(VK_DOWN) != KEY_FREE)
	{
		MyRect temp = mapObj.m_tRect;

		temp.pos.y += 100.0f * MAINTIMER.getOneFrameTimeF();

		if (temp.pos.y > mapObj.m_VPreset.m_pTexture->m_TextureDesc.Height - 100)
		{
			temp.pos.y = mapObj.m_VPreset.m_pTexture->m_TextureDesc.Height - 100;
		}

		mapObj.setTexPos(temp.pos.x, temp.pos.y);
	}

	mapObj.frame();
	return true;
}

bool TestCase::render()
{
	mapObj.render();
	return true;
}

bool TestCase::release()
{
	mapObj.release();
	return true;
}

GAME_RUN(Move View, 1086, 919)