#include "mytimer.h"

FLOAT MyTimer::getGametime()
{
    return gameTime / 1000.0f;
}

FLOAT MyTimer::getOneFrameTime()
{
    return oneFrameTime / 1000.0f;
}

bool MyTimer::init()
{
    stTime = timeGetTime();
    curTime = 0;
    timer = 0;
    counter = 0;
    
    return true;
}

bool MyTimer::frame()
{
    counter++;
    curTime = timeGetTime();

    oneFrameTime = curTime - stTime;
    timer += oneFrameTime;
    gameTime += oneFrameTime;

    if (timer > 1000)
    {
        timer -= 1000;
        fps = counter;
        counter = 0;
    }
    
    stTime = curTime;
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

FLOAT MyHighResolutionTimer::getGametime()
{
    return gameTime.QuadPart / (FLOAT)frequency.QuadPart;
}

FLOAT MyHighResolutionTimer::getOneFrameTime()
{
    return oneFrameTime.QuadPart / (FLOAT)frequency.QuadPart;
}

DWORD MyHighResolutionTimer::getFps()
{
    return fps;
}

bool MyHighResolutionTimer::init()
{
    QueryPerformanceFrequency(&frequency);
    gameTime = {0};
    oneFrameTime = { 0 };
    fps = { 0 };

    QueryPerformanceCounter(&stTime);
    curTime = { 0 };
    timer = { 0 };
    return true;
}

bool MyHighResolutionTimer::frame()
{
    counter++;
    QueryPerformanceCounter(&curTime);

    oneFrameTime.QuadPart = curTime.QuadPart - stTime.QuadPart;
    timer.QuadPart += oneFrameTime.QuadPart;
    gameTime.QuadPart += oneFrameTime.QuadPart;

    if (timer.QuadPart > frequency.QuadPart)
    {
        timer.QuadPart -= frequency.QuadPart;
        fps = counter;
        counter = 0;
    }

    stTime.QuadPart = curTime.QuadPart;
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
