#pragma once
#include "mynode.h"
#include "mycollision.h"

class MySpacePartition
{
public:
	virtual ~MySpacePartition();
	virtual void resetAllDynamicList() = 0;
	virtual void addStaticObject(MyObject* pBObj) = 0;
	virtual void addDynamicObject(MyObject* pBObj) = 0;
	virtual MyShape* getBoundary() = 0;
	virtual void create(MyShape* pShape) = 0;

	virtual void getCollisionList(const MyObject* pDObj, vector<MyObject*>& objList) = 0;
	virtual void clear() = 0;
};

class QuadTree : public MySpacePartition
{
public:
	QuadTreeNode* pRoot;
	int maxDepth;

public:
	QuadTree();
	QuadTree(int maxDepth);
	QuadTree(float x, float y, float width, float height, int maxDepth = 3);
	QuadTree(MyVector2F pos, MyVector2F fWH, int maxDepth = 3);
	QuadTree(MyRect rect, int maxDepth = 3);
	~QuadTree();

	void create(float x, float y, float width, float height);
	void create(MyVector2F pos, MyVector2F fWH);
	void buildTree(QuadTreeNode* pTarget);
	QuadTreeNode* createNode(float x, float y, float width, float height, int depth = 0);
	QuadTreeNode* createNode(MyRect nPos, int depth = 0);
	QuadTreeNode* findPutNode(MyObject2F* pBObj);
	QuadTreeNode* findPutNodeSub(QuadTreeNode* pTarget, MyObject2F* pBObj);

	void create(MyShape* pShape) override;
	void addStaticObject(MyObject* pBObj) override;
	void addDynamicObject(MyObject* pBObj) override;
	MyShape* getBoundary() override;
	void resetAllDynamicList() override;
	void getCollisionList(const MyObject* pDObj, vector<MyObject*>& objList) override;
	void getCollisionListSub(const MyObject2F* pDObj, const QuadTreeNode* pTarget,
		vector<MyObject*>& objList);
	void clear() override;

	void resetSubTreeDList(QuadTreeNode* pTarget);
	void clearSub(QuadTreeNode* pTarget);
};

class Octree : public MySpacePartition
{
public:
	OctTreeNode* pRoot;
	int maxDepth;

public:
	Octree();
	Octree(int maxDepth);
	Octree(float x, float y, float z,
		float width, float length, float height, int maxDepth = 3);
	Octree(MyVector3F pos, MyVector3F fWLH, int maxDepth = 3);
	Octree(MyCube cube, int maxDepth = 3);
	~Octree();

	void create(float x, float y, float z,
		float width, float length, float height);
	void create(MyVector3F pos, MyVector3F fWLH);
	void buildTree(OctTreeNode* pTarget);
	OctTreeNode* createNode(float x, float y, float z,
		float width, float length, float height, int depth = 0);
	OctTreeNode* createNode(MyCube nPos, int depth = 0);
	OctTreeNode* findPutNode(MyObject3F* pBObj);
	OctTreeNode* findPutNodeSub(OctTreeNode* pTarget, MyObject3F* pBObj);

	void create(MyShape* pShape) override;
	void addStaticObject(MyObject* pBObj) override;
	void addDynamicObject(MyObject* pBObj) override;
	MyShape* getBoundary() override;
	void resetAllDynamicList() override;
	void getCollisionList(const MyObject* pDObj, vector<MyObject*>& objList) override;
	void getCollisionListSub(const MyObject3F* pDObj, const OctTreeNode* pTarget,
		vector<MyObject*>& objList);
	void clear() override;

	void resetSubTreeDList(OctTreeNode* pTarget);
	void clearSub(OctTreeNode* pTarget);
};
