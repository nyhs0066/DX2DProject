#include "mygamecore.h"

MyGameCore::MyGameCore()
{
	wireFrameFlag = false;
}

MyGameCore::~MyGameCore()
{
	release();
	coreRelease();
}

bool MyGameCore::init()
{
	return true;
}

bool MyGameCore::frame()
{
	return true;
}

bool MyGameCore::render()
{
	return true;
}

bool MyGameCore::release()
{
	return true;
}

BOOL MyGameCore::run()
{
	if (!coreInit()) { return false; }

	BOOL runFlag = true;

	while (runFlag)
	{
		if (!MyWindow::run()) { runFlag = false; }
		else
		{
			if (isResized())
			{
				if (!resizeDevice()) { runFlag = false; continue; };
			}
			if (!coreFrame() || !coreRender()) { runFlag = false; }
		}
	}

	coreRelease();
	return runFlag;
}

bool MyGameCore::coreInit()
{
	if (FAILED(DEVICE_MANAGER.create())) { return false; }
	DEVICE_MANAGER.init();

	if (FAILED(RENDER_MANAGER.create())) { return false; }
	RENDER_MANAGER.init();

	if (FAILED(TEXT_WRITER.create(I_SWAPCHAIN))) { return false; };
	TEXT_WRITER.init();

	if (FAILED(EFFECT_STATE.create())) { return false; }
	EFFECT_STATE.init();

	SOUND_MANAGER.init();

	//unused
	/*SHADER_MANAGER.init();
	TEXTURE_MANAGER.init();
	SPRITE_MANAGER.init();
	*/

	MAINTIMER.init();
	MAININPUT.init();

	iPrevWidth = MyWindow::cWidth;
	iPrevHeight = MyWindow::cHeight;

	init();

	return true;
}

bool MyGameCore::coreFrame()
{
	MAINTIMER.frame();
	MAININPUT.frame();
	SOUND_MANAGER.frame();

	//unused
	/*DEVICE_MANAGER.frame();
	RENDER_MANAGER.frame();
	SHADER_MANAGER.frame();
	TEXTURE_MANAGER.frame();
	TEXT_WRITER.frame();
	EFFECT_STATE.frame();
	SPRITE_MANAGER.init();*/

	//TO DO

	frame();


	return true;
}

bool MyGameCore::corePreRender()
{
	PRE_RENDER();

	I_DCONTEXT->PSSetSamplers(0, 1, EFFECT_STATE.m_pSStateWrapPoint.GetAddressOf());

	//끝 인수로 들어가는 샘플 마스크 비트값의 기본 설정값은 0xffffffff
	//UINT이므로 -1 = 0xffffffff
	I_DCONTEXT->OMSetBlendState(EFFECT_STATE.m_pBStateAlphaBlend.Get(), nullptr, -1);

	MAINTIMER.render();
	
	//unused
	/*DEVICE_MANAGER.render();
	RENDER_MANAGER.render();
	SHADER_MANAGER.render();
	TEXTURE_MANAGER.render();
	TEXT_WRITER.render();
	MAININPUT.render();
	SOUND_MANAGER.render();
	EFFECT_STATE.render();
	SPRITE_MANAGER.init();
	*/

	return true;
}

bool MyGameCore::coreRender()
{
	corePreRender();
	render();
	corePostRender();
	return true;
}

bool MyGameCore::corePostRender()
{
#ifdef _DEBUG
	wstring myTime;

	myTime += L"RunningT : " + std::to_wstring(MAINTIMER.getRunningTimeF()) + L"\n";
	myTime += L"1FrameT : " + std::to_wstring(MAINTIMER.getOneFrameTimeF()) + L"\n";
	myTime += L"FPS : " + std::to_wstring(MAINTIMER.getFps()) + L"\n";

	TEXT_WRITER.drawT(myTime.c_str(), 0, 0, { 0.3f, 0.0f, 0.77f, 1.0f });

	if (MAININPUT.getKeyState(VK_CONTROL) == KEY_DOWN) { wireFrameFlag = !wireFrameFlag; }

	if (wireFrameFlag) { I_DCONTEXT->RSSetState(EFFECT_STATE.m_pRStateWireFrame.Get()); }
	else { I_DCONTEXT->RSSetState(EFFECT_STATE.m_pRStateSolid.Get()); }
#endif //_DEBUG

	POST_RENDER();
	return true;
}

bool MyGameCore::coreRelease()
{
	release();

	SPRITE_MANAGER.release();
	EFFECT_STATE.release();
	SOUND_MANAGER.release();
	MAININPUT.release();
	MAINTIMER.release();
	TEXTURE_MANAGER.release();
	SHADER_MANAGER.release();
	TEXT_WRITER.release();
	RENDER_MANAGER.release();
	DEVICE_MANAGER.release();
	return true;
}

bool MyGameCore::isResized()
{
	if ((iPrevWidth != MyWindow::cWidth) || (iPrevHeight != MyWindow::cHeight))
	{
		return true;
	}
	return false;
}

bool MyGameCore::resizeDevice()
{
	HRESULT hr = S_OK;

	hr = RENDER_MANAGER.resizeRenderTarget(MyWindow::cWidth, MyWindow::cHeight);
	if (FAILED(hr)) { return false; }

	iPrevWidth = MyWindow::cWidth;
	iPrevHeight = MyWindow::cHeight;
	return true;
}
