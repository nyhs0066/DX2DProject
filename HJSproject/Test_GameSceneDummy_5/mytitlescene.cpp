#include "mytitlescene.h"

MyTitleScene::MyTitleScene()
{
}

MyTitleScene::~MyTitleScene()
{
    release();
}

bool MyTitleScene::init()
{
    titleBGM = LOAD_SOUND(L"../../data/sound/Slim_Bobby-aviino.mp3");
    startbuttonpush = LOAD_SOUND(L"../../data/sound/button_start.wav");

    titleBGM->play(true);

    LOAD_SPRITE(L"../../data/ui/test_UI_list.txt");

    pPlayButton = std::make_shared<MyUIButton>();
    pPlayButton->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pPlayButton->setSprite(L"test_play");
    pPlayButton->setPosRect({ MyWindow::cWidth * 0.5f - 64.0f, MyWindow::cHeight * 0.75f - 64.0f,
    128.0f, 128.0f });

    /*pSettingButton = std::make_shared<MyUIButton>();
    pSettingButton->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/Pixel_Art_Buttons.png");
    pSettingButton->setSprite(L"test_setting");
    pSettingButton->setPosRect({ MyWindow::cWidth - 96.0f, 32.0f,
    64.0f, 64.0f });*/

    MyUserInterface* pSettingimage = new MyUserInterface;
    pSettingimage->create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/ui/setting.png");
    pSettingimage->setPosRect({ MyWindow::cWidth - 80.0f, 44.0f,
    32.0f, 32.0f });

    /*pSettingButton->addChild(pSettingimage);*/

    BG.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/background/crumpled_paper.jpg");
    BG.setPosRect({ 0.0f, 0.0f, (FLOAT)MyWindow::cWidth, (FLOAT)MyWindow::cHeight });
    
    //alphabet layout
    MyExRect pRect;
    pRect = { (FLOAT)MyWindow::cWidth * 0.25f , (FLOAT)MyWindow::cHeight * 0.175f,  150.0f, 150.0f };
    p1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/p.png");
    p1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.35f , (FLOAT)MyWindow::cHeight * 0.175f,  150.0f, 150.0f };
    a1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/a.png");
    a1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.45f , (FLOAT)MyWindow::cHeight * 0.175f,  150.0f, 150.0f };
    p2.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/p.png");
    p2.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.55f , (FLOAT)MyWindow::cHeight * 0.175f,  150.0f, 150.0f };
    e1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/e.png");
    e1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.65f , (FLOAT)MyWindow::cHeight * 0.175f,  150.0f, 150.0f };
    r1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/r.png");
    r1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.3f , (FLOAT)MyWindow::cHeight * 0.4f,  150.0f, 150.0f };
    w1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/w.png");
    w1.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.4f , (FLOAT)MyWindow::cHeight * 0.4f,  150.0f, 150.0f };
    a2.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/a.png");
    a2.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.5f , (FLOAT)MyWindow::cHeight * 0.4f,  150.0f, 150.0f };
    r2.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/r.png");
    r2.setPosRect(pRect);
    pRect = { (FLOAT)MyWindow::cWidth * 0.6f , (FLOAT)MyWindow::cHeight * 0.4f,  150.0f, 150.0f };
    s1.create(L"../../data/shader/mydefaultshader.txt",
        L"../../data/sprite_set/test_sprites/hand_drawn_alphabet/s.png");
    s1.setPosRect(pRect);

    bSceneFlag = 0;

    return true;
}

//bSceneFlag ¼ø¼­ : 1 title / 2 in game / 3 gameover / 4 clear / 5 exit
bool MyTitleScene::frame()
{
    BG.frame();
    BG.postFrame();

    pPlayButton->frame();
    if (pPlayButton->m_bState == UB_SELECT) 
    { 
        //play button select 
        bSceneFlag = 2; 
        startbuttonpush->playEffect();
    }
    pPlayButton->postFrame();

    /*pSettingButton->frame();*/
    //if (pSettingButton->m_bState == UB_SELECT) 
    //{ 
    //    //setting button select
    //    bSceneFlag = 0; 
    //} 
    //pSettingButton->postFrame();

    p1.postFrame();
    a1.postFrame();
    p2.postFrame();
    e1.postFrame();
    r1.postFrame();
    w1.postFrame();
    a2.postFrame();
    r2.postFrame();
    s1.postFrame();

    return true;
}

bool MyTitleScene::render()
{
    BG.render();
    pPlayButton->render();
   /* pSettingButton->render();*/

    p1.render();
    a1.render();
    p2.render();
    e1.render();
    r1.render();
    w1.render();
    a2.render();
    r2.render();
    s1.render();
    return true;
}

bool MyTitleScene::release()
{
    if (pPlayButton.get()) { pPlayButton->release(); }
    /*if (pSettingButton.get()) { pSettingButton->release(); }*/
    BG.release();

    p1.release();
    a1.release();
    p2.release();
    e1.release();
    r1.release();
    w1.release();
    a2.release();
    r2.release();
    s1.release();

    bSceneFlag = 0;

    if (titleBGM) { titleBGM->stop(); }
    return true;
}
