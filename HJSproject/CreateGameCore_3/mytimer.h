#pragma once
#include "myunih.h"

//timeapi.h(windows.h�� ����) winmm.lib ���
class MyTimer	
{
public:
	DWORD gameTime;
	DWORD oneFrameTime;
	DWORD fps;

	DWORD stTime;
	DWORD curTime;
	DWORD timer;
	DWORD counter;

	FLOAT getGametime();
	FLOAT getOneFrameTime();

	bool init();
	bool frame();
	bool render();
	bool release();
};

//profileapi.h (windows.h�� ����)
class MyHighResolutionTimer	: public Singleton<MyHighResolutionTimer>
{
	friend class Singleton<MyHighResolutionTimer>;
private:
	LARGE_INTEGER gameTime;
	LARGE_INTEGER oneFrameTime;
	DWORD fps;

	LARGE_INTEGER frequency;
	LARGE_INTEGER stTime;
	LARGE_INTEGER curTime;
	LARGE_INTEGER timer;
	DWORD counter;

public:
	FLOAT getGametime();
	FLOAT getOneFrameTime();
	DWORD getFps();

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define I_TIMER MyHighResolutionTimer::getInstance()