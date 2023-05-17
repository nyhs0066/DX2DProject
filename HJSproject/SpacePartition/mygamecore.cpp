#include "mygamecore.h"

MyGameCore::MyGameCore()
{
	initialization();
}

MyGameCore::~MyGameCore() 
{
	release();
	delete pSpace;
	delete pPlayer;
}

void MyGameCore::initialization()
{
	pSpace = nullptr;
	pPlayer = nullptr;
}

void MyGameCore::frame(float deltaT, float gameT)
{
	MyShape* boundary = pSpace->getBoundary();
	pPlayer->frame(boundary, deltaT, gameT);

	pSpace->resetAllDynamicList();
	for (auto it : dynamicObjList)
	{
		it->frame(boundary, deltaT, gameT);
		pSpace->addDynamicObject(it);
	}
}

void MyGameCore::draw()
{
	pSpace->getCollisionList(pPlayer, collisionList);

	pPlayer->draw();
	for (auto it : collisionList) { it->draw(); }

	collisionList.clear();
}

void MyGameCore::release()
{
	dynamicObjList.clear();
	collisionList.clear();
	for (int i = 0; i < allObjlist.size(); i++) { delete allObjlist[i]; }
	allObjlist.clear();
}

void MyGameCore::run()
{
	float delayT = 100;
	float deltaT = delayT / 1000.0f;
	float runningTime = 0.0f;

	time_t st, ed;

	while (runningTime < 30.0f)
	{
		st = time(0);

		frame(deltaT, runningTime);
		draw();

		ed = time(0);

		Sleep(delayT - (ed - st));
		system("cls");
		runningTime += deltaT;
		cout << "Running time : " << runningTime << "s \n";
	}
}