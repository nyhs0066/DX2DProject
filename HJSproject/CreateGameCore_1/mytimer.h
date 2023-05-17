#pragma once
#include "myunih.h"

class MyTimer	//timeapi.h(windows.h�� ����) winmm.lib ���
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

class MyHighResolutionTimer	//profileapi.h (windows.h�� ����)
{
public:
	LARGE_INTEGER frequency;
	LARGE_INTEGER gameTime;
	LARGE_INTEGER oneFrameTime;
	DWORD fps;

	LARGE_INTEGER stTime;
	LARGE_INTEGER curTime;
	LARGE_INTEGER timer;
	DWORD counter;
	
	FLOAT getGametime();
	FLOAT getOneFrameTime();

	bool init();
	bool frame();
	bool render();
	bool release();
};