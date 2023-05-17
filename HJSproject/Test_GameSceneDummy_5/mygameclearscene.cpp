#include "mygameclearscene.h"

bool MyGameClearScene::loadResource()
{
    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
    gameClearBGM = LOAD_SOUND(L"../../data/sound/Pixelland.mp3");

    return true;
}

bool MyGameClearScene::init()
{
    bSceneFlag = 0;

    loadResource();

    gameClearBGM->play(true);

    pButtonGroup = std::make_shared<MyUIListControl>();
    pButtonGroup->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/UI_empty_list.png");
    MyExRect UIPRect;
    UIPRect.fWH = { 100.0f * 4 + 20.0f * 3, 120.0f };
    UIPRect.pos = { MyWindow::cWidth * 0.5f - UIPRect.fWH.x * 0.5f, 700.0f };
    pButtonGroup->setPosRect(UIPRect);

    //첫번째 버튼
    MyExRect pRect;
    MyUserInterface* pTemp = new MyUIButton;
    pTemp->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pTemp->setSprite(L"test_back_title");
    pRect = { MyWindow::cWidth * 0.5f - UIPRect.fWH.x * 0.5f + 50.0f, 700.0f + 17.5f, 100.0f, 100.0f };
    pTemp->setPosRect(pRect);

    pButtonGroup->addChild(pTemp);

    //두번째 버튼
    pTemp = new MyUIButton;
    pTemp->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pTemp->setSprite(L"test_setting");
    pRect.pos.x += 130.0f;
    pTemp->setPosRect(pRect);

    MyUserInterface* pSettingimage = new MyUserInterface;
    pSettingimage->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/restart.png");
    pSettingimage->setPosRect({ pRect.pos.x + 10.0f, pRect.pos.y, 80.0f, 80.0f });

    pTemp->addChild(pSettingimage);

    pButtonGroup->addChild(pTemp);

    //세번째 버튼
    pTemp = new MyUIButton;
    pTemp->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pTemp->setSprite(L"test_setting");
    pRect.pos.x += 130.0f;
    pTemp->setPosRect(pRect);

    pSettingimage = new MyUserInterface;
    pSettingimage->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/x.png");
    pSettingimage->setPosRect({ pRect.pos.x + 10.0f, pRect.pos.y, 80.0f, 80.0f });

    pTemp->addChild(pSettingimage);

    pButtonGroup->addChild(pTemp);

    gameClearBGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/gameover.jpg");
    gameClearBGObj.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

    //alphabet layout
    pRect = { (FLOAT)MyWindow::cWidth * 0.25f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    c1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/c.png");
    c1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.35f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    l1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/l.png");
    l1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.45f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    e1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/e.png");
    e1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.55f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    a1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/a.png");
    a1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.65f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    r1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/r.png");
    r1.setPosRect(pRect);

    return true;
}

bool MyGameClearScene::frame()
{
    gameClearBGObj.postFrame();
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
        bSceneFlag = 5;
    }

    c1.postFrame();
    l1.postFrame();
    e1.postFrame();
    a1.postFrame();
    r1.postFrame();

    return true;
}

bool MyGameClearScene::render()
{
    gameClearBGObj.render();
    pButtonGroup->render();

    c1.render();
    l1.render();
    e1.render();
    a1.render();
    r1.render();

    return true;
}

bool MyGameClearScene::release()
{
    if (gameClearBGM) { gameClearBGM->stop(); }

    gameClearBGObj.release();
    if (pButtonGroup.get()) { pButtonGroup->release(); };

    c1.release();
    l1.release();
    e1.release();
    a1.release();
    r1.release();

    bSceneFlag = 0;

    return true;
}
