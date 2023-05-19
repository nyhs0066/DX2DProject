#include "mypausescene.h"

bool MyPauseScene::loadResource()
{
    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
    return true;
}

bool MyPauseScene::init()
{
    loadResource();

    pBackTitleButton = std::make_shared<MyUIButton>();
    pBackTitleButton->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pBackTitleButton->setSprite(L"test_back_title");
    pBackTitleButton->setPosRect({ MyWindow::cWidth - 192.0f, MyWindow::cHeight - 192.0f,
        128.0f, 128.0f });

    //Pause BG Set
    pauseBGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/pause_background.png");
    pauseBGObj.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

    return true;
}

bool MyPauseScene::frame()
{
    if (pBackTitleButton->m_bState == UB_SELECT)
    {
        bSceneFlag = 1;
    }

    pauseBGObj.frame();
    pauseBGObj.postFrame();
    pBackTitleButton->frame();
    pBackTitleButton->postFrame();

    return true;
}

bool MyPauseScene::render()
{
    pauseBGObj.render();
    pBackTitleButton->render();

    return true;
}

bool MyPauseScene::release()
{
    pauseBGObj.release();
    if (pBackTitleButton.get()) { pBackTitleButton->release(); }

    bSceneFlag = 0;

    return true;
}
