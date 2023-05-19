#include "mytimer.h"

MyHighResolutionTimer::MyHighResolutionTimer()
{
	ZeroMemory(&m_frequency, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_runningTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_oneFrameTick, sizeof(LARGE_INTEGER));

	ZeroMemory(&m_timer, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_prevTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_curTime, sizeof(LARGE_INTEGER));

	m_counter = 0;
	m_framePerSecond = 0;
}

MyHighResolutionTimer::~MyHighResolutionTimer()
{
	release();
}

bool MyHighResolutionTimer::init()
{
	BOOL res = TRUE;

	res = QueryPerformanceFrequency(&m_frequency);
	if (!res) { return FALSE; }

	QueryPerformanceCounter(&m_prevTime);

	return res;
}

bool MyHighResolutionTimer::frame()
{
	QueryPerformanceCounter(&m_curTime);
	m_counter++;

	m_oneFrameTick.QuadPart = m_curTime.QuadPart - m_prevTime.QuadPart;

	m_runningTick.QuadPart += m_oneFrameTick.QuadPart;
	m_timer.QuadPart += m_oneFrameTick.QuadPart;

	if (m_timer.QuadPart > m_frequency.QuadPart)
	{
		m_timer.QuadPart -= m_frequency.QuadPart;
		m_framePerSecond = m_counter;
		m_counter = 0;
	}

	m_prevTime = m_curTime;

	return true;
}

bool MyHighResolutionTimer::render()
{
	return true;
}
bool MyHighResolutionTimer::release()
{
	return true;
}

DWORD MyHighResolutionTimer::getFps()
{
	return m_framePerSecond;
}

LARGE_INTEGER MyHighResolutionTimer::getRunningTick()
{
	return m_runningTick;
}

LARGE_INTEGER MyHighResolutionTimer::getOneFrameTick()
{
	return m_oneFrameTick;
}

float MyHighResolutionTimer::getRunningTimeF()
{
	return (FLOAT)m_runningTick.QuadPart / m_frequency.QuadPart;
}

float MyHighResolutionTimer::getOneFrameTimeF()
{
	return (FLOAT)m_oneFrameTick.QuadPart / m_frequency.QuadPart;
}

MyTimer::MyTimer()
{
	m_runningTick = 0;
	m_oneFrameTick = 0;

	m_timer = 0;
	m_prevTime = 0;
	m_curTime = 0;

	m_counter = 0;
	m_framePerSecond = 0;
}

MyTimer::~MyTimer()
{
	release();
}

bool MyTimer::init()
{
	m_prevTime = timeGetTime();

	return true;
}

bool MyTimer::frame()
{
	m_counter++;
	m_curTime = timeGetTime();

	m_oneFrameTick = m_curTime - m_prevTime;

	m_runningTick += m_oneFrameTick;
	m_timer += m_oneFrameTick;

	if (m_timer > 1000)
	{
		m_timer -= 1000;
		m_framePerSecond = m_counter;
		m_counter = 0;
	}

	m_prevTime = m_curTime;

	return true;
}

bool MyTimer::render()
{
	return true;
}
bool MyTimer::release()
{
	return true;
}

DWORD MyTimer::getFps()
{
	return m_framePerSecond;
}

DWORD MyTimer::getRunningTick()
{
	return m_runningTick;
}

DWORD MyTimer::getOneFrameTick()
{
	return m_oneFrameTick;
}

float MyTimer::getRunningTimeF()
{
	return (FLOAT)m_runningTick / 1000;
}

float MyTimer::getOneFrameTimeF()
{
	return (FLOAT)m_oneFrameTick / 1000;
}
