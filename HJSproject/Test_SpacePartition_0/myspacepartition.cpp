#include "myspacepartition.h"

QuadTree::QuadTree() : QuadTree(2) {}

QuadTree::QuadTree(int maxDepth)
{
	pRoot = nullptr;
	this->maxDepth = maxDepth;
}

QuadTree::QuadTree(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int maxDepth)
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
	create(rect);
}

QuadTree::~QuadTree()
{
	clear();
}

void QuadTree::create(FLOAT x, FLOAT y, FLOAT width, FLOAT height)
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

void QuadTree::create(MyRect rt)
{
	if (!pRoot)
	{
		pRoot = createNode(rt);

		buildTree(pRoot);
	}
}

void QuadTree::buildTree(QuadTreeNode* pTarget)
{
	if (pTarget)
	{
		if (pTarget->depth < maxDepth)
		{
			FLOAT dx = pTarget->nPos.fWH.v[0] / 2.0f;
			FLOAT dy = pTarget->nPos.fWH.v[1] / 2.0f;

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

QuadTreeNode* QuadTree::createNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth)
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

QuadTreeNode* QuadTree::findPutNode(MyObject2D* pBObj)
{
	QuadTreeNode* pFind = nullptr;

	if (pRoot && pBObj) { pFind = findPutNodeSub(pRoot, pBObj); }
	return pFind;
}

QuadTreeNode* QuadTree::findPutNodeSub(QuadTreeNode* pTarget, MyObject2D* pBObj)
{
	QuadTreeNode* pFind = nullptr;
	QuadTreeNode* pTemp = nullptr;

	MyObject2D* pObj = dynamic_cast<MyObject2D*>(pBObj);

	if (MyCollision::rectToRect(pTarget->nPos, pObj->getCollisionRect()) == MYCT_IN)
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

void QuadTree::addStaticObject(MyObject2D* pBObj)
{
	MyObject2D* pSObj = pBObj;
	if (pSObj)
	{
		QuadTreeNode* pFind = findPutNode(pSObj);
		if (pFind) { pFind->staticObjList.push_back(pSObj); }
	}
}

void QuadTree::addDynamicObject(MyObject2D* pBObj)
{
	MyObject2D* pDObj = pBObj;
	if (pDObj)
	{
		QuadTreeNode* pFind = findPutNode(pDObj);
		if (pFind) { pFind->dynamicObjList.push_back(pDObj); }
	}
}

MyRect QuadTree::getBoundary()
{
	return pRoot->nPos;
}

void QuadTree::resetAllDynamicList()
{
	if (pRoot) { resetSubTreeDList(pRoot); }
}

void QuadTree::getCollisionList(const MyObject2D* pBObj, vector<MyObject2D*>& objList)
{
	const MyObject2D* pDObj = pBObj;

	if (pDObj) { getCollisionListSub(pDObj, pRoot, objList); }
}

void QuadTree::getCollisionListSub(const MyObject2D* pDObj, const QuadTreeNode* pTarget,
	vector<MyObject2D*>& objList)
{
	for (int i = 0; i < pTarget->staticObjList.size(); i++)
	{
		if (MyCollision::rectToRect(pDObj->getCollisionRect(), pTarget->staticObjList[i]->getCollisionRect()))
		{
			objList.push_back(pTarget->staticObjList[i]);
		}
	}

	for (int i = 0; i < pTarget->dynamicObjList.size(); i++)
	{
		if (MyCollision::rectToRect(pDObj->getCollisionRect(), pTarget->dynamicObjList[i]->getCollisionRect()))
		{
			objList.push_back(pTarget->dynamicObjList[i]);
		}
	}

	for (int i = 0; i < pTarget->pChild.size(); i++)
	{
		if (MyCollision::rectToRect(pTarget->pChild[i]->nPos, pDObj->getCollisionRect()))
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