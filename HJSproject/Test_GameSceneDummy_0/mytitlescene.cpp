#include "mytitlescene.h"

MyTitleScene::MyTitleScene()
{
}

MyTitleScene::~MyTitleScene()
{
}

bool MyTitleScene::init()
{
    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");

    pPlayButton = std::make_shared<MyUIButton>();
    pPlayButton->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pPlayButton->setSprite(L"test_play");
    pPlayButton->setPosRect({ MyWindow::cWidth * 0.5f - 64.0f, MyWindow::cHeight * 0.75f - 64.0f,
    128.0f, 128.0f });

    pSettingButton = std::make_shared<MyUIButton>();
    pSettingButton->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pSettingButton->setSprite(L"test_setting");
    pSettingButton->setPosRect({ MyWindow::cWidth - 96.0f, 32.0f,
    64.0f, 64.0f });

    MyUserInterface* pSettingimage = new MyUserInterface;
    pSettingimage->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/setting.png");
    pSettingimage->setPosRect({ MyWindow::cWidth - 80.0f, 44.0f,
    32.0f, 32.0f });

    pSettingButton->addChild(pSettingimage);

    bSceneFlag = 0;

    return true;
}

bool MyTitleScene::frame()
{
    pPlayButton->frame();
    if (pPlayButton->m_bState == UB_SELECT) 
    { 
        //play button select 
        bSceneFlag = 1; 
    }
    pPlayButton->postFrame();

    pSettingButton->frame();
    if (pSettingButton->m_bState == UB_SELECT) 
    { 
        //setting button select
        bSceneFlag = 2; 
    } 
    pSettingButton->postFrame();
    return true;
}

bool MyTitleScene::render()
{
    pPlayButton->render();
    pSettingButton->render();
    return true;
}

bool MyTitleScene::release()
{
    if (pPlayButton.get()) { pPlayButton->release(); }
    if (pSettingButton.get()) { pSettingButton->release(); }
    return true;
}
