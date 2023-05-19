#pragma once
#include "myunih.h"
#include "mynode.h"
#include "mycollision.h"

class QuadTree : public Singleton<QuadTree>
{
	friend class Singleton<QuadTree>;
public:
	QuadTreeNode* pRoot;
	int maxDepth;

public:
	QuadTree();
	QuadTree(int maxDepth);
	QuadTree(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int maxDepth = 3);
	QuadTree(MyVector2F pos, MyVector2F fWH, int maxDepth = 3);
	QuadTree(MyExRect rect, int maxDepth = 3);
	~QuadTree();

	void create(FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	void create(MyVector2F pos, MyVector2F fWH);
	void create(MyExRect rt);
	void buildTree(QuadTreeNode* pTarget);

	QuadTreeNode* createNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth = 0);
	QuadTreeNode* createNode(MyExRect nPos, int depth = 0);
	QuadTreeNode* findPutNode(MyObject2D* pBObj);
	QuadTreeNode* findPutNodeSub(QuadTreeNode* pTarget, MyObject2D* pBObj);

	void addStaticObject(MyObject2D* pBObj);
	void addDynamicObject(MyObject2D* pBObj);
	MyExRect getBoundary();
	void resetAllDynamicList();

	void getStaticCollisionList(const MyObject2D* pDObj, vector<MyObject2D*>& objList);
	void getStaticCollisionListSub(const MyObject2D* pDObj, const QuadTreeNode* pTarget,
		vector<MyObject2D*>& objList);
	void getDynamicCollisionList(const MyObject2D* pDObj, vector<MyObject2D*>& objList);
	void getDynamicCollisionListSub(const MyObject2D* pDObj, const QuadTreeNode* pTarget,
		vector<MyObject2D*>& objList);
	void clear();

	void resetSubTreeDList(QuadTreeNode* pTarget);
	void clearSub(QuadTreeNode* pTarget);
};

#define MYSPACE QuadTree::getInstance()