#pragma once
#include "myscenemanager.h"

#define MAX_ENEMY_NUMBER 20

class MyInGameScene : public MyScene
{
public:
	vector<wstring> rPaths;

	MyCamera mainCam;
	MyExRect BoundaryRect;

	MyMapObject* platForms;
	vector<MyObject2D*> staticCList;
	vector<MyObject2D*> dynamicCList;
	MyExRect instRt;

	std::vector<MyEffect*> ePresetList;

	std::list<MyEffect*> playerEffectList;
	std::vector<std::list<MyEffect*>::const_iterator> playerEffectDeleteList;

	std::list<MyEffect*> enemyEffectList;
	std::vector<std::list<MyEffect*>::const_iterator> enemyEffectDeleteList;

	std::list<MyEffect*>::iterator it;
	std::list<MyEffect*>::const_iterator cit;

	std::list<MyEnemy*>::iterator eit;
	std::list<MyEnemy*>::const_iterator ecit;

	std::vector<std::list<MyEffect*>::const_iterator> deleteList;
	std::list<MyEffect*> effectDeleteList;

	std::list<MyEnemy*> enemyList;
	std::vector<std::list<MyEnemy*>::const_iterator> enemyDeleteList;

	MyBackGroundObject BGObj;
	MyMovementTestDummy dummy;

	MyUserInterface* pReinforceUI;

	FLOAT enemySpawnTimer;

	MyStackBar w1bar;
	MyStackBar w2bar;
	MyStackBar w3bar;

	FLOAT enemyHealthMultiflier;

	MyFirstBoss Left;
	MyFirstBoss Right;

	bool loadResource();
	
	bool init() override;
	bool frame() override;
	bool postFrame();
	bool render() override;
	bool release() override;

	void randomEnemySpawn();
	void gamePlatformSet();
};