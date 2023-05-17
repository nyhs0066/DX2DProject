#include "mybinarysearchtree.h"
#include "myavltree.h"
#include "mytwothreetree.h"
#include "myredblacktree.h"
#include "myhashtable.h"
#include <random>

#define VERIFIED

std::random_device rd;
std::default_random_engine gen(rd());
std::uniform_int_distribution<int> dist(0, 50);

int main()
{
#ifndef VERIFIED
	

	AVLTree test;

	for (int i = 0; i < 25; i++)
	{
		test.insertTNode(test.createTNode(dist(gen)));
		test.inOrderTraversal(test.getRoot());
	}

	for (int i = 0; i < 10; i++)
	{
		test.inOrderTraversal(test.getRoot());

		cout << '\n';
		cout << "Delete " << test.getRoot()->getData() << '\n';
		test.deleteTNode(test.getRoot());
	}

	RedBlackTree test;
	for (int i = 0; i < 50; i++)
	{
		test.insertTNode(test.createTNode(dist(gen)));
		test.inOrderTraversal(test.getRoot());
	}
	cout << "\nEND\n";

	for (int i = 0; i < 50; i++)
	{
		test.levelOrderTraversal(test.getRoot());

		cout << '\n';
		cout << "Delete " << test.getRoot()->getData() << '\n';
		test.deleteTNode(test.getRoot());
	}

	HashTable test;

	Bucket** testList = new Bucket * [10];

	testList[0] = new Bucket("FIRST", "ACON");
	testList[1] = new Bucket("SECOND", "BUNNY");
	testList[2] = new Bucket("THIRD", "CAT");
	testList[3] = new Bucket("FOURTH", "DOG");
	testList[4] = new Bucket("FIFTH", "ELEPHANT");
	testList[5] = new Bucket("SIXTH", "FOX");
	testList[6] = new Bucket("SEVENTH", "GOAT");
	testList[7] = new Bucket("EIGHTTH", "HORSE");
	testList[8] = new Bucket("NINTH", "IGUANA");
	testList[9] = new Bucket("TENTH", "JAGUAR");

	for (int i = 0; i < 10; i++)
	{
		test.insert(testList[i]);
	}

	Bucket* finding = test.search("FIFTH");
	if (finding)
	{
		cout << finding->data << '\n';
	}
	else
	{
		cout << "Data is Not found\n";
	}

	test.deleteBucket("FIFTH");

	finding = test.search("FIFTH");
	if (finding)
	{
		cout << finding->data << '\n';
	}
	else
	{
		cout << "Data is Not found\n";
	}
#endif //VERIFIED END

	vector<int> test;
	test.resize(20);
	cout << ' ';
}