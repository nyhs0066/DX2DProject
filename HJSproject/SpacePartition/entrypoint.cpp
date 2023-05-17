#include "mygamecore.h"
#include <random>

constexpr float MINPOS = 0.0f, MAXPOS = 256.0f;
constexpr float MINWHL = 0.0f, MAXWHL = 16.0f;
constexpr float MINF = -3.0f, MAXF = 3.0f;
constexpr int DEFAULTMAXDEPTH = 3;

random_device rd;
default_random_engine gen(rd());
uniform_real_distribution<float> posDist(MINPOS + 8.0f, MAXPOS - 8.0f);
uniform_real_distribution<float> whDist(MINWHL + 2.0f, MAXWHL - 2.0f);
uniform_real_distribution<float> fDist(MINF, MAXF);

int main()
{
	MyGameCore test;

	/*float mid = (MINPOS + MAXPOS) / 2.0f;
	float size = 16.0f;

	test.pSpace = new QuadTree(MINPOS, MINPOS, MAXPOS, MAXPOS, DEFAULTMAXDEPTH);

	Player2F* myPlayer = new Player2F(mid, mid, size, size);
	myPlayer->addForce(MyVector2F(fDist(gen), fDist(gen)));
	test.pPlayer = myPlayer;

	int cnt = 0;

	for (; cnt < 100; cnt++)
	{
		MyObject* newSObj = new MyObject2F(posDist(gen), posDist(gen),
			whDist(gen), whDist(gen));
		test.allObjlist.insert(std::make_pair(cnt, newSObj));
		test.pSpace->addStaticObject(newSObj);
	}

	for (; cnt < 200; cnt++)
	{
		MyDynamicObject2F* newDObj = new MyDynamicObject2F(posDist(gen), posDist(gen),
			whDist(gen), whDist(gen));
		newDObj->addForce(MyVector2F(fDist(gen), fDist(gen)));
		test.allObjlist.insert(std::make_pair(cnt, newDObj));
		test.dynamicObjList.push_back(newDObj);
		test.pSpace->addDynamicObject(newDObj);
	}*/

	float mid = (MINPOS + MAXPOS) / 2.0f;
	float size = 64.0f;

	test.pSpace = new Octree(MINPOS, MINPOS, MINPOS, MAXPOS, MAXPOS, MAXPOS, DEFAULTMAXDEPTH);

	Player3F* myPlayer = new Player3F(mid, mid, mid, size, size, size);
	myPlayer->addForce(MyVector3F(fDist(gen), fDist(gen), fDist(gen)));
	test.pPlayer = myPlayer;

	int cnt = 0;

	for (; cnt < 100; cnt++)
	{
		MyObject* newSObj = new MyObject3F(posDist(gen), posDist(gen),
			posDist(gen), whDist(gen), whDist(gen), whDist(gen));
		test.allObjlist.insert(std::make_pair(cnt, newSObj));
		test.pSpace->addStaticObject(newSObj);
	}

	for (; cnt < 200; cnt++)
	{
		MyDynamicObject3F* newDObj = new MyDynamicObject3F(posDist(gen), posDist(gen),
			posDist(gen), whDist(gen), whDist(gen), whDist(gen));
		newDObj->addForce(MyVector3F(fDist(gen), fDist(gen), fDist(gen)));
		test.allObjlist.insert(std::make_pair(cnt, newDObj));
		test.dynamicObjList.push_back(newDObj);
		test.pSpace->addDynamicObject(newDObj);
	}

	test.run();
}