#include "myspacepartition.h"

MySpacePartition::~MySpacePartition() {}

QuadTree::QuadTree() : QuadTree(2) {}

QuadTree::QuadTree(int maxDepth)
{
	pRoot = nullptr;
	this->maxDepth = maxDepth;
}

QuadTree::QuadTree(float x, float y, float width, float height, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(x, y, width, height);
}

QuadTree::QuadTree(MyVector2F pos, MyVector2F fWH, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(pos, fWH);
}

QuadTree::QuadTree(MyRect rect, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(&rect);
}

QuadTree::~QuadTree()
{
	clear();
}

void QuadTree::create(float x, float y, float width, float height)
{
	if(!pRoot)
	{
		MyRect nPos(x, y, width, height);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void QuadTree::create(MyVector2F pos, MyVector2F fWH)
{
	if (!pRoot)
	{
		MyRect nPos(pos, fWH);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void QuadTree::create(MyShape* pShape)
{
	MyRect* rect = dynamic_cast<MyRect*>(pShape);
	if (!pRoot)
	{
		MyRect nPos(*rect);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void QuadTree::buildTree(QuadTreeNode* pTarget)
{
	if (pTarget)
	{
		if (pTarget->depth < maxDepth)
		{
			float dx = pTarget->nPos.fWH.p[0] / 2.0f;
			float dy = pTarget->nPos.fWH.p[1] / 2.0f;

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					pTarget->pChild.push_back(createNode(
								pTarget->nPos.pos.x + j * dx,
								pTarget->nPos.pos.y + i * dy,
								dx, dy, pTarget->depth + 1) );

					pTarget->pChild[i * 2 + j]->pParent = pTarget;
					buildTree(dynamic_cast<QuadTreeNode*>(pTarget->pChild[i * 2 + j]));
				}
			}
		}
	}
}

QuadTreeNode* QuadTree::createNode(float x, float y, float width, float height, int depth)
{
	QuadTreeNode* newNode = new QuadTreeNode(x, y, width, height);
	assert(newNode);
	newNode->depth = depth;
	return newNode;
}

QuadTreeNode* QuadTree::createNode(MyRect nPos, int depth)
{
	QuadTreeNode* newNode = new QuadTreeNode(nPos);
	assert(newNode);
	newNode->depth = depth;
	return newNode;
}

QuadTreeNode* QuadTree::findPutNode(MyObject2F* pBObj)
{
	QuadTreeNode* pFind = nullptr;

	if (pRoot && pBObj) { pFind = findPutNodeSub(pRoot, pBObj); }
	return pFind;
}

QuadTreeNode* QuadTree::findPutNodeSub(QuadTreeNode* pTarget, MyObject2F* pBObj)
{
	QuadTreeNode* pFind = nullptr;
	QuadTreeNode* pTemp = nullptr;

	MyObject2F* pObj = dynamic_cast<MyObject2F*>(pBObj);

	if (MyCollision::rectToRect(pTarget->nPos, pObj->posRect) == CT_IN)
	{
		pFind = pTarget;

		if (pTarget->pChild.size())
		{
			for (int i = 0; i < 4; i++)
			{
				pTemp = findPutNodeSub(pTarget->pChild[i], pObj);
				if (pTemp) { return pTemp; }
			}
		}
	}

	return pFind;
}

void QuadTree::addStaticObject(MyObject* pBObj)
{
	MyObject2F* pSObj = dynamic_cast<MyObject2F*>(pBObj);
	if (pSObj)
	{
		QuadTreeNode* pFind = findPutNode(pSObj);
		if (pFind) { pFind->staticObjList.push_back(pSObj); }
	}
}

void QuadTree::addDynamicObject(MyObject* pBObj)
{
	MyDynamicObject2F* pDObj = dynamic_cast<MyDynamicObject2F*>(pBObj);
	if (pDObj)
	{
		QuadTreeNode* pFind = findPutNode(pDObj);
		if (pFind) { pFind->dynamicObjList.push_back(pDObj); }
	}
}

MyShape* QuadTree::getBoundary()
{
	return &(pRoot->nPos);
}

void QuadTree::resetAllDynamicList()
{
	if (pRoot) { resetSubTreeDList(pRoot); }
}

void QuadTree::getCollisionList(const MyObject* pBObj, vector<MyObject*>& objList)
{
	const MyObject2F* pDObj = dynamic_cast<const MyObject2F*>(pBObj);

	if (pDObj) { getCollisionListSub(pDObj, pRoot, objList); }
}

void QuadTree::getCollisionListSub(const MyObject2F* pDObj, const QuadTreeNode* pTarget,
	vector<MyObject*>& objList)
{
	for (int i = 0; i < pTarget->staticObjList.size(); i++)
	{
		if (MyCollision::circleToCircle(pDObj->posCircle, pTarget->staticObjList[i]->posCircle))
		{
			if (MyCollision::rectToRect(pDObj->posRect, pTarget->staticObjList[i]->posRect))
			{
				objList.push_back(pTarget->staticObjList[i]);
			}
		}
	}

	for (int i = 0; i < pTarget->dynamicObjList.size(); i++)
	{
		if (MyCollision::circleToCircle(pDObj->posCircle, pTarget->dynamicObjList[i]->posCircle))
		{
			if (MyCollision::rectToRect(pDObj->posRect, pTarget->dynamicObjList[i]->posRect))
			{
				objList.push_back(pTarget->dynamicObjList[i]);
			}
		}
	}

	for (int i = 0; i < pTarget->pChild.size(); i++)
	{
		if (MyCollision::rectToRect(pTarget->pChild[i]->nPos, pDObj->posRect))
		{
			getCollisionListSub(pDObj, pTarget->pChild[i], objList);
		}
	}
}

void QuadTree::resetSubTreeDList(QuadTreeNode* pTarget)
{
	pTarget->dynamicObjList.clear();

	if (pTarget->pChild.size())
	{
		for (int i = 0; i < 4; i++) { resetSubTreeDList(pTarget->pChild[i]); }
	}
}

void QuadTree::clear()
{
	if (pRoot) 
	{ 
		clearSub(pRoot); 
		pRoot = nullptr;
	}
}

void QuadTree::clearSub(QuadTreeNode* pTarget)
{
	if (pTarget->pChild.size())
	{
		for (int i = 0; i < 4; i++) { clearSub(pTarget->pChild[i]); }
	}
	delete pTarget;
	pTarget = nullptr;
}

Octree::Octree() : Octree(2) {}

Octree::Octree(int maxDepth)
{
	pRoot = nullptr;
	this->maxDepth = maxDepth;
}

Octree::Octree(float x, float y, float z, float width, float length, float height, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(x, y, z, width, length, height);
}

Octree::Octree(MyVector3F pos, MyVector3F fWLH, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(pos, fWLH);
}

Octree::Octree(MyCube cube, int maxDepth)
{
	this->maxDepth = maxDepth;
	create(&cube);
}

Octree::~Octree()
{
	clear();
}

void Octree::create(float x, float y, float z, float width, float length, float height)
{
	if (!pRoot)
	{
		MyCube nPos(x, y, z, width, length, height);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void Octree::create(MyVector3F pos, MyVector3F fWLH)
{
	if (!pRoot)
	{
		MyCube nPos(pos, fWLH);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void Octree::create(MyShape* pShape)
{
	MyCube* cube = dynamic_cast<MyCube*>(pShape);
	if (!pRoot)
	{
		MyCube nPos(*cube);
		pRoot = createNode(nPos);

		buildTree(pRoot);
	}
}

void Octree::buildTree(OctTreeNode* pTarget)
{
	if (pTarget->depth < maxDepth)
	{
		float dx = pTarget->nPos.fWLH.p[0] / 2.0f;
		float dy = pTarget->nPos.fWLH.p[1] / 2.0f;
		float dz = pTarget->nPos.fWLH.p[2] / 2.0f;

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					pTarget->pChild.push_back(createNode(
						pTarget->nPos.pos.x + k * dx,
						pTarget->nPos.pos.y + j * dy,
						pTarget->nPos.pos.z + i * dz,
						dx, dy, dz, pTarget->depth + 1) );

					pTarget->pChild[i * 4 + j * 2 + k]->pParent = pTarget;
					buildTree(pTarget->pChild[i * 4 + j * 2 + k]);
				}
			}
		}
	}
}

OctTreeNode* Octree::createNode(float x, float y, float z, float width, float length, float height, int depth)
{
	OctTreeNode* newNode = new OctTreeNode(x, y, z,  width, length, height);
	assert(newNode);
	newNode->depth = depth;
	return newNode;
}

OctTreeNode* Octree::createNode(MyCube nPos, int depth)
{
	OctTreeNode* newNode = new OctTreeNode(nPos);
	assert(newNode);
	newNode->depth = depth;
	return newNode;
}

OctTreeNode* Octree::findPutNode(MyObject3F* pBObj)
{
	OctTreeNode* pFind = nullptr;

	if (pRoot && pBObj) { pFind = findPutNodeSub(pRoot, pBObj); }
	return pFind;
}

OctTreeNode* Octree::findPutNodeSub(OctTreeNode* pTarget, MyObject3F* pBObj)
{
	OctTreeNode* pFind = nullptr;
	OctTreeNode* pTemp = nullptr;

	if (MyCollision::cubeToCube(pTarget->nPos, pBObj->posCube) == CT_IN)
	{
		pFind = pTarget;

		if (pTarget->pChild.size())
		{
			for (int i = 0; i < 8; i++)
			{
				pTemp = findPutNodeSub(pTarget->pChild[i], pBObj);
				if (pTemp) { return pTemp; }
			}
		}
	}

	return pFind;
}

void Octree::addStaticObject(MyObject* pBObj)
{
	MyObject3F* pSObj = dynamic_cast<MyObject3F*>(pBObj);
	if (pSObj)
	{
		OctTreeNode* pFind = findPutNode(pSObj);
		if (pFind) { pFind->staticObjList.push_back(pSObj); }
	}
}

void Octree::addDynamicObject(MyObject* pBObj)
{
	MyDynamicObject3F* pDObj = dynamic_cast<MyDynamicObject3F*>(pBObj);
	if (pDObj)
	{
		OctTreeNode* pFind = findPutNode(pDObj);
		if (pFind) { pFind->dynamicObjList.push_back(pDObj); }
	}
}

MyShape* Octree::getBoundary()
{
	return &(pRoot->nPos);
}

void Octree::resetAllDynamicList()
{
	if (pRoot) { resetSubTreeDList(pRoot); }
}

void Octree::getCollisionList(const MyObject* pBObj, vector<MyObject*>& objList)
{
	const MyObject3F* pDObj = dynamic_cast<const MyObject3F*>(pBObj);

	if (pDObj) { getCollisionListSub(pDObj, pRoot, objList); }
}

void Octree::getCollisionListSub(const MyObject3F* pDObj, const OctTreeNode* pTarget,
	vector<MyObject*>& objList)
{
	for (int i = 0; i < pTarget->staticObjList.size(); i++)
	{
		if (MyCollision::sphereToSphere(pDObj->posSphere, pTarget->staticObjList[i]->posSphere))
		{
			if (MyCollision::cubeToCube(pDObj->posCube, pTarget->staticObjList[i]->posCube))
			{
				objList.push_back(pTarget->staticObjList[i]);
			}
		}
	}

	for (int i = 0; i < pTarget->dynamicObjList.size(); i++)
	{
		if (MyCollision::sphereToSphere(pDObj->posSphere, pTarget->dynamicObjList[i]->posSphere))
		{
			if (MyCollision::cubeToCube(pDObj->posCube, pTarget->dynamicObjList[i]->posCube))
			{
				objList.push_back(pTarget->dynamicObjList[i]);
			}
		}
	}

	for (int i = 0; i < pTarget->pChild.size(); i++)
	{
		if (MyCollision::cubeToCube(pTarget->nPos, pDObj->posCube))
		{
			getCollisionListSub(pDObj, pTarget->pChild[i], objList);
		}
	}
}

void Octree::resetSubTreeDList(OctTreeNode* pTarget)
{
	pTarget->dynamicObjList.clear();

	if (pTarget->pChild.size())
	{
		for (int i = 0; i < 8; i++) { resetSubTreeDList(pTarget->pChild[i]); }
	}
}

void Octree::clear()
{
	if (pRoot) 
	{ 
		clearSub(pRoot); 
		pRoot = nullptr;
	}
}

void Octree::clearSub(OctTreeNode* pTarget)
{
	if (pTarget->pChild.size())
	{
		for (int i = 0; i < 8; i++) { clearSub(pTarget->pChild[i]); }
	}
	delete pTarget;
	pTarget = nullptr;
}