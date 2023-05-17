#pragma once
#include "mygamecore.h"
#include "mybaseobject.h"
#include "mymapobject.h"
#include "myplayer.h"
#include "mycollision.h"
#include "mybackgroundobject.h"
#include "mycamera.h"
#include "myspritemanager.h"
#include "myeffect.h"
#include "myspacepartition.h"
#include "myuserinterface.h"

#define FIXFRAMET 1.0f / 60.0f

class MyScene
{
public:
	wstring wszSceneName;

	MyScene();
	virtual ~MyScene();

	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};

class MySceneManager : public Singleton<MySceneManager>
{
	friend class Singleton<MySceneManager>;
private:
	map<wstring, std::unique_ptr<MyScene>> m_sceneMap;

	MySceneManager();
	~MySceneManager();

public:
	bool addScene(wstring wszSceneName, std::unique_ptr<MyScene>& pScene);
	MyScene* getScene(wstring wszSceneName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define SCENE_MANAGER MySceneManager::getInstance()