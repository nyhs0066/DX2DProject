#include "mypausescene.h"

bool MyPauseScene::loadResource()
{
    return true;
}

bool MyPauseScene::init()
{
    //Pause BG Set
    pauseBGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/pause_background.png");
    pauseBGObj.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

    return true;
}

bool MyPauseScene::frame()
{
    pauseBGObj.frame();

    return true;
}

bool MyPauseScene::render()
{
    pauseBGObj.render();

    return true;
}

bool MyPauseScene::release()
{
    pauseBGObj.release();

    return true;
}
