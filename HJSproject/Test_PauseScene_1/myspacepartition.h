#pragma once
#include "mynode.h"
#include "mycollision.h"

class QuadTree
{
public:
	QuadTreeNode* pRoot;
	int maxDepth;

public:
	QuadTree();
	QuadTree(int maxDepth);
	QuadTree(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int maxDepth = 3);
	QuadTree(MyVector2F pos, MyVector2F fWH, int maxDepth = 3);
	QuadTree(MyRect rect, int maxDepth = 3);
	~QuadTree();

	void create(FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	void create(MyVector2F pos, MyVector2F fWH);
	void create(MyRect rt);
	void buildTree(QuadTreeNode* pTarget);

	QuadTreeNode* createNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth = 0);
	QuadTreeNode* createNode(MyRect nPos, int depth = 0);
	QuadTreeNode* findPutNode(MyObject2D* pBObj);
	QuadTreeNode* findPutNodeSub(QuadTreeNode* pTarget, MyObject2D* pBObj);

	void addStaticObject(MyObject2D* pBObj);
	void addDynamicObject(MyObject2D* pBObj);
	MyRect getBoundary();
	void resetAllDynamicList();
	void getCollisionList(const MyObject2D* pDObj, vector<MyObject2D*>& objList);
	void getCollisionListSub(const MyObject2D* pDObj, const QuadTreeNode* pTarget,
		vector<MyObject2D*>& objList);
	void clear();

	void resetSubTreeDList(QuadTreeNode* pTarget);
	void clearSub(QuadTreeNode* pTarget);
};
