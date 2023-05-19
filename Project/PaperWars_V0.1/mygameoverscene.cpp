#include "mygameoverscene.h"

bool MyGameOverScene::loadResource()
{
    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");
    gameoverBGM = LOAD_SOUND(L"../../data/sound/secret_entrance.mp3");

    return true;
}


bool MyGameOverScene::init()
{
    bSceneFlag = 0;

    loadResource();

    gameoverBGM->play(true);

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

    //alphabet layout
    pRect = { (FLOAT)MyWindow::cWidth * 0.07f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    g1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/g.png");
    g1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.17f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    a1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/a.png");
    a1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.27f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    m1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/m.png");
    m1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.37f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    e1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/e.png");
    e1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.55f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    o1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/o.png");
    o1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.65f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    v1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/v.png");
    v1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.75f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    e2.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/e.png");
    e2.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.85f , (FLOAT)MyWindow::cHeight * 0.275f,  150.0f, 150.0f };
    r1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/r.png");
    r1.setPosRect(pRect);

    gameOverBGObj.create(L"../../data/shader/mydefaultshader.txt", L"../../data/background/gameover.jpg");
    gameOverBGObj.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });

    return true;
}

//bSceneFlag 순서 : 1 title / 2 in game / 3 gameover / 4 clear / 5 exit
bool MyGameOverScene::frame()
{
    gameOverBGObj.postFrame();
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

    g1.postFrame();
    a1.postFrame();
    m1.postFrame();
    e1.postFrame();
    o1.postFrame();
    v1.postFrame();
    e2.postFrame();
    r1.postFrame();

    return true;
}

bool MyGameOverScene::render()
{
    gameOverBGObj.render();
    pButtonGroup->render();

    g1.render();
    a1.render();
    m1.render();
    e1.render();
    o1.render();
    v1.render();
    e2.render();
    r1.render();

    return true;
}

bool MyGameOverScene::release()
{
    if (gameoverBGM) { gameoverBGM->stop(); }

    gameOverBGObj.release();
    if (pButtonGroup.get()) { pButtonGroup->release(); };

    g1.release();
    a1.release();
    m1.release();
    e1.release();
    o1.release();
    v1.release();
    e2.release();
    r1.release();

    bSceneFlag = 0;

    return true;
}
