#include "mytwothreetree.h"

TwoThreeNode::TwoThreeNode()
{
	data[0] = data[1] = EMPTY;
	for (int i = 0; i < 3; i++) { pChild[i] = nullptr; }
}

TwoThreeNode::~TwoThreeNode()
{
}

int TwoThreeNode::getData(bool idx)
{
	return data[idx];
}

void TwoThreeNode::setData(bool idx, int data)
{
	this->data[idx] = data;
}

TwoThreeTree::TwoThreeTree()
{
	pRoot = nullptr;
}

TwoThreeTree::~TwoThreeTree()
{
	clearTree();
}

TwoThreeNode* TwoThreeTree::getRoot()
{
	return pRoot;
}

void TwoThreeTree::insertData(int data)
{
	
}

void TwoThreeTree::deleteData(int key)
{
}

TwoThreeNode* TwoThreeTree::getMinimum(TwoThreeNode* pTarget)
{
	if (pTarget)
	{
		while (pTarget->pChild[0]) { pTarget = pTarget->pChild[0]; }
	}
	return pTarget;
}

TwoThreeNode* TwoThreeTree::getMaximum(TwoThreeNode* pTarget)
{
	if (pTarget)
	{
		while (pTarget->pChild[2]) { pTarget = pTarget->pChild[2]; }
	}
	return pTarget;
}

void TwoThreeTree::inOrderTraversal(TwoThreeNode* pRoot)
{
}

TwoThreeNode* TwoThreeTree::search(int key)
{
	return nullptr;
}

TwoThreeNode* TwoThreeTree::transPlant(TwoThreeNode* dest, TwoThreeNode* source)
{
	return nullptr;
}

void TwoThreeTree::clearTree()
{
}
