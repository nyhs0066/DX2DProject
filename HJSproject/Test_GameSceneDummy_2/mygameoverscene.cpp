#include "mygameoverscene.h"

bool MyGameOverScene::loadResource()
{
    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
    return true;
}

bool MyGameOverScene::init()
{
    bSceneFlag = 0;

    loadResource();

    pButtonGroup = std::make_shared<MyUIListControl>();
    pButtonGroup->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/UI_empty_list.png");
    MyExRect UIPRect = { .0f, 50.0f, 100.0f * 4 + 20.0f * 3, 120.0f };
    pButtonGroup->setPosRect(UIPRect);

    for (int i = 0; i < 3; i++)
    {
        MyUserInterface* pTemp = new MyUIButton;
        pTemp->create(L"../../data/shader/mydefaultshader.txt",
            L"../../data/ui/Pixel_Art_Buttons.png");
        pTemp->setSprite(L"test_setting");
        UIPRect = { 60.0f + 120.0f * i, 10.0f + 50.0f, 100.0f, 100.0f };
        pTemp->setPosRect(UIPRect);

        pButtonGroup->addChild(pTemp);
    }

    //Pause BG Set
    //gameOverBGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/pause_background.png");
    //gameOverBGObj.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

    return true;
}

bool MyGameOverScene::frame()
{
    //gameOverBGObj.frame();
    //gameOverBGObj.postFrame();
    pButtonGroup->frame();
    pButtonGroup->postFrame();

    if (pButtonGroup->getChild(0)->m_bState == UB_SELECT)
    {
        bSceneFlag = 1;
    }
    else if (pButtonGroup->getChild(1)->m_bState == UB_SELECT)
    {
        bSceneFlag = 2;
    }
    else if (pButtonGroup->getChild(2)->m_bState == UB_SELECT)
    {
        bSceneFlag = 3;
    }

    return true;
}

bool MyGameOverScene::render()
{
    //gameOverBGObj.render();
    pButtonGroup->render();

    return true;
}

bool MyGameOverScene::release()
{
    //gameOverBGObj.release();
    if (pButtonGroup.get()) { pButtonGroup->release(); };

    bSceneFlag = 0;

    return true;
}
