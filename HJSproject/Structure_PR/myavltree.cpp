#include "myavltree.h"

AVLTNode::AVLTNode() : TNode()
{
	height = 0;
}

AVLTNode::AVLTNode(int data) : TNode(data)
{
	height = 0;
}

AVLTNode::~AVLTNode()
{
}

int AVLTNode::getHeight()
{
	return height;
}

void AVLTNode::setHeight(int height)
{
	this->height = height;
}

AVLTNode* AVLTNode::left()
{
	return dynamic_cast<AVLTNode*>(pLeft);
}

AVLTNode* AVLTNode::right()
{
	return dynamic_cast<AVLTNode*>(pRight);
}

AVLTNode* AVLTNode::parent()
{
	return dynamic_cast<AVLTNode*>(pParent);
}

AVLTree::AVLTree() : BinarySearchTree()
{

}

AVLTree::~AVLTree()
{
}

AVLTNode* AVLTree::createTNode(int data)
{
	AVLTNode* pNewE = new AVLTNode(data);
	assert(pNewE);
	return pNewE;
}

AVLTNode* AVLTree::getRoot()
{
	return dynamic_cast<AVLTNode*>(this->pRoot);
}

void AVLTree::insertTNode(AVLTNode* pNewE)
{
	BinarySearchTree::insertTNode(pNewE);
	rebalance(pNewE);
}

void AVLTree::deleteTNode(AVLTNode* pTarget)
{
	if (pTarget)
	{
		AVLTNode* pCur = nullptr;

		if (!pTarget->pLeft) 
		{ 
			pCur = pTarget->right();
			LLrotate(pTarget, pCur);
			pCur->pLeft = nullptr;
		}
		else if (!pTarget->pRight) 
		{ 
			pCur = pTarget->left();
			RRrotate(pTarget, pCur);
			pCur->pRight = nullptr;
		}
		else
		{
			AVLTNode* temp = dynamic_cast<AVLTNode*>(getMaximum(pTarget->pLeft));
			if (temp->pParent != pTarget)
			{
				pCur = temp->left();
				transPlant(temp, temp->pLeft);		//왼쪽 서브트리를 이동할 노드 위치로 이동
				temp->pLeft = pTarget->pLeft;		//이동할 노드의 왼쪽 노드를 삭제할 노드의 왼쪽노드로 지정
				pTarget->pLeft->pParent = temp;		//삭제할 노드 왼쪽 노드의 부모 노드 갱신
			}

			if (!pCur) { pCur = temp; }
			transPlant(pTarget, temp);
			temp->pRight = pTarget->pRight;			//이동할 노드의 오른쪽 노드를 삭제할 노드의 왼쪽노드로 지정
			pTarget->pRight->pParent = temp;		//삭제할 노드 오른쪽 노드의 부모 노드 갱신
		}

		delete pTarget;
		pTarget = nullptr;

		rebalance(pCur);
	}
}


void AVLTree::LLrotate(AVLTNode* A, AVLTNode* B)
{
	A->pRight = B->pLeft;
	if (B->pLeft) { B->pLeft->pParent = A; }

	B->pParent = A->pParent;
	if (A->pParent)
	{
		if (A->pParent->pLeft == A) { A->pParent->pLeft = B; }
		else { A->pParent->pRight = B; }
	}
	else { pRoot = B; }

	B->pLeft = A;
	A->pParent = B;

	resetHeight(A);
	resetHeight(B);
}

void AVLTree::RRrotate(AVLTNode* A, AVLTNode* B)
{
	A->pLeft = B->pRight;
	if (B->pRight) { B->pRight->pParent = A; }

	B->pParent = A->pParent;
	if (A->pParent)
	{
		if (A->pParent->pRight == A) { A->pParent->pRight = B; }
		else { A->pParent->pLeft = B; }
	}
	else { pRoot = B; }

	B->pRight = A;
	A->pParent = B;

	resetHeight(A);
	resetHeight(B);
}

void AVLTree::LRrotate(AVLTNode* A, AVLTNode* B, AVLTNode* C)
{
	LLrotate(B, C);
	RRrotate(A, C);
}

void AVLTree::RLrotate(AVLTNode* A, AVLTNode* B, AVLTNode* C)
{
	RRrotate(B, C);
	LLrotate(A, C);
}

void AVLTree::rebalance(AVLTNode* pCur)
{
	int BF = 0;
	AVLTNode* pLeft, * pRight;

	while (pCur)
	{
		resetHeight(pCur);
		BF = factorCheck(pCur);

		if (BF > 1)
		{
			pLeft = pCur->left();
			if (factorCheck(pLeft) > 0) { RRrotate(pCur, pLeft); }
			else
			{
				pRight = pLeft->right();
				LRrotate(pCur, pLeft, pRight);
			}
		}
		else if (BF < -1)
		{
			pRight = pCur->right();
			if (factorCheck(pRight) < 0) { LLrotate(pCur, pRight); }
			else
			{
				pLeft = pRight->left();
				RLrotate(pCur, pRight, pLeft);
			}
		}

		pCur = pCur->parent();
	}
}

int AVLTree::factorCheck(AVLTNode* pTarget)
{
	AVLTNode* pLeft = pTarget->left();
	AVLTNode* pRight = pTarget->right();

	int BalanceFactor = 0;
	if (pLeft) { BalanceFactor += pLeft->getHeight(); }
	if (pRight) { BalanceFactor -= pRight->getHeight(); }

	return BalanceFactor;
}

void AVLTree::resetHeight(AVLTNode* pTarget)
{
	if (pTarget)
	{
		int LH, RH;
		LH = RH = 0;

		AVLTNode* pLeft = pTarget->left();
		AVLTNode* pRight = pTarget->right();

		if (pLeft) { LH = pLeft->getHeight(); }
		if (pRight) { RH = pRight->getHeight(); }

		pTarget->setHeight(max(LH, RH) + 1);
	}
}
