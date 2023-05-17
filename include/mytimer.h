#pragma once
#include "myunih.h"

#pragma comment (lib, "winmm.lib")

class MyHighResolutionTimer : public Singleton<MyHighResolutionTimer>
{
	friend class Singleton<MyHighResolutionTimer>;

private:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_runningTick;
	LARGE_INTEGER m_oneFrameTick;

	LARGE_INTEGER m_timer;
	LARGE_INTEGER m_prevTime;
	LARGE_INTEGER m_curTime;

	DWORD m_counter;
	DWORD m_framePerSecond;

	MyHighResolutionTimer();
	~MyHighResolutionTimer();

public:
	bool init();
	bool frame();
	bool render();
	bool release();

	DWORD getFps();

	LARGE_INTEGER getRunningTick();
	LARGE_INTEGER getOneFrameTick();
	float getRunningTimeF();
	float getOneFrameTimeF();
};

class MyTimer
{
private:
	DWORD m_runningTick;
	DWORD m_oneFrameTick;

	DWORD m_timer;
	DWORD m_prevTime;
	DWORD m_curTime;

	DWORD m_counter;
	DWORD m_framePerSecond;

public:
	MyTimer();
	~MyTimer();

	bool init();
	bool frame();
	bool render();
	bool release();

	DWORD getFps();

	DWORD getRunningTick();
	DWORD getOneFrameTick();
	float getRunningTimeF();
	float getOneFrameTimeF();
};

#define MAINTIMER MyHighResolutionTimer::getInstance()
