#include "myredblacktree.h"

RBTNode::RBTNode() : TNode()
{
	color = RED;
}

RBTNode::~RBTNode()
{
}

void RBTNode::setColor(bool color)
{
	this->color = color;
}

bool RBTNode::getColor()
{
	return color;
}

RBTNode* RBTNode::left()
{
	return dynamic_cast<RBTNode*>(this->pLeft);
}

RBTNode* RBTNode::right()
{
	return dynamic_cast<RBTNode*>(this->pRight);
}

RBTNode* RBTNode::parent()
{
	return dynamic_cast<RBTNode*>(this->pParent);
}

RedBlackTree::RedBlackTree()
{
}

RedBlackTree::~RedBlackTree()
{
}

RBTNode* RedBlackTree::createTNode(int data)
{
	RBTNode* pNewE = new RBTNode;
	assert(pNewE);
	pNewE->setData(data);
	return pNewE;
}

RBTNode* RedBlackTree::getRoot()
{
	return dynamic_cast<RBTNode*>(pRoot);
}

void RedBlackTree::insertTNode(RBTNode* pNewE)
{
	if (!pNewE) { return; }

	TNode* trailingPointer = nullptr;
	TNode* cur = pRoot;

	while (cur)
	{
		trailingPointer = cur;
		if (pNewE->getData() <= cur->getData()) { cur = cur->pLeft; }
		else { cur = cur->pRight; }
	}

	pNewE->pParent = trailingPointer;
	if (!trailingPointer) { pRoot = pNewE; }
	else
	{
		if (pNewE->getData() <= trailingPointer->getData())
		{
			trailingPointer->pLeft = pNewE;
		}
		else
		{
			trailingPointer->pRight = pNewE;
		}
	}
	insertFix(pNewE);
}

void RedBlackTree::deleteTNode(RBTNode* pTarget)
{
	//pTarget노드는 삭제과정에서 특성을 위반할 수 있는 노드를 가리킨다.
	//pTarget노드의 색깔에 따라 Property 5를 위반하는지 아닌지가 나뉜다.
	//pFixStart는 특성 위반을 검증해야하는 시작노드를 가리킨다.
	if (pTarget)
	{
		RBTNode* pDeleteMe = pTarget;			//삭제할 노드

		bool targetColor = pTarget->getColor();
		RBTNode* pFixStart = nullptr;			//특성 위반 조사 시작 노드
		RBTNode* pFixParent = pTarget;			//시작 노드의 부모 노드

		if (!pTarget->left())
		{
			pFixStart = pTarget->right();		//올라가는 오른쪽 노드가 위반 여부 대상
			transPlant(pDeleteMe, pTarget->right());
		}
		else if (!pTarget->right())
		{
			pFixStart = pTarget->left();		//올라가는 왼쪽 노드가 위반 여부 대상
			transPlant(pDeleteMe, pTarget->left());
		}
		else
		{
			pTarget = dynamic_cast<RBTNode*>(getMaximum(pDeleteMe->left()));
			targetColor = pTarget->getColor();
			pFixStart = pTarget->left();
			pFixParent = pTarget;
			if (pTarget->parent() != pDeleteMe)
			{
				transPlant(pTarget, pTarget->left());
				pFixParent = pTarget->parent();
				pTarget->pLeft = pDeleteMe->pLeft;
				pDeleteMe->pLeft->pParent = pTarget;
			}
			transPlant(pDeleteMe, pTarget);
			pTarget->pRight = pDeleteMe->pRight;
			pDeleteMe->pRight->pParent = pTarget;
			pTarget->setColor(pDeleteMe->getColor());
		}

		if (targetColor == BLACK) { deleteFix(pFixStart, pFixParent); }

		delete pDeleteMe;
		pTarget = nullptr;
	}
}

bool RedBlackTree::getColor(RBTNode* pTarget)
{
	if (pTarget) { return pTarget->getColor(); }
	return BLACK;
}

void RedBlackTree::setColor(RBTNode* pTarget, bool color)
{
	if (pTarget) { pTarget->setColor(color); }
}

void RedBlackTree::Lrotate(RBTNode* A, RBTNode* B)
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
}

void RedBlackTree::Rrotate(RBTNode* A, RBTNode* B)
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
}

void RedBlackTree::insertFix(RBTNode* pTarget)
{
	//작업에 있어 트리가 특성을 지키는 가가 중요
	//property 2, 4가 주요 위반 사항이며 이를 재조정한다.
	//이 작업을 수행하는 동안 property 1, 3을 위반하지 않는다.
	//property 5는 회전으로 재조정한다.

	//pGrandParent는 루프 시작에는 항상 BLACK이다.
	//RR위반(Property 4)이 일어나려면 pGrandParent가 Red이면 무조건 자식이 Black이기 때문
	RBTNode* pUncle;
	RBTNode* pGrandParent;	
	RBTNode* temp;

	//두번째 조건의 전제가 부모의 부모가 존재한다는 것을 입증한다.
	while (getColor(pTarget->parent()) == RED) //property 4 violation
	{
		pGrandParent = pTarget->parent()->parent();
		if (pGrandParent->left() == pTarget->parent())
		{
			pUncle = pGrandParent->right();
			if (getColor(pUncle) == RED)	//
			{
				//case 1 : pUncle is red
				setColor(pUncle, BLACK);
				setColor(pTarget->parent(), BLACK);
				setColor(pGrandParent, RED);
				pTarget = pGrandParent;
			}
			else if (pTarget->parent()->right() == pTarget)
			{
				//case 2 : pUncle is black && target is right child of its parent
				temp = pTarget->parent();
				Lrotate(pTarget->parent(), pTarget);
				pTarget = temp;
			}
			else
			{
				//case 3 : pUncle is black && target is left child of its parent
				setColor(pTarget->parent(), BLACK);
				setColor(pGrandParent, RED);	//property 5 violation
				Rrotate(pGrandParent, pTarget->parent());
			}
		}
		else
		{
			pUncle = pGrandParent->left();
			if (pUncle && pUncle->getColor() == RED)	//
			{
				//case 1 : pUncle is red
				setColor(pUncle, BLACK);
				setColor(pTarget->parent(), BLACK);
				setColor(pGrandParent, RED);
				pTarget = pGrandParent;
			}
			else if (pTarget->parent()->left() == pTarget)
			{
				//case 2 : pUncle is black && target is left child of its parent
				temp = pTarget->parent();
				Rrotate(pTarget->parent(), pTarget);
				pTarget = temp;
			}
			else
			{
				//case 3 : pUncle is black && target is right child of its parent
				setColor(pTarget->parent(), BLACK);
				setColor(pGrandParent, RED);	//property 5 violation
				Lrotate(pGrandParent, pTarget->parent()); //recover property 4, 5
			}
		}
	}
	setColor(getRoot(), BLACK);	//recover property 2
}

void RedBlackTree::deleteFix(RBTNode* pTarget, RBTNode* pTParent)
{
	//삽입이 pUncle노드의 색이 중요했다면 삭제는 sibling노드가 중요하다.
	//black노드 개수를 신경써야하는 부분
	//	A. 최종적으로 sibling쪽 black 노드의 개수에 변화를 주지 않을 것
	//	B. target노드를 포함한 경로의 Black 개수 1개를 복원할 것

	//주요 특성 위반 사항은 2, 5번
	RBTNode* pSibling = nullptr;
	while (pTarget != pRoot && getColor(pTarget) == BLACK)
	{
		if (pTarget) { pTParent = pTarget->parent(); }

		if (pTParent->left() == pTarget)
		{
			pSibling = pTParent->right();

			//case 1 : sibling is red => convert one of cases : case 2 or 3 or 4
			if (getColor(pSibling) == RED)
			{
				pTParent->setColor(RED);
				pSibling->setColor(BLACK);		//부모와 색을 스위치해 A를 보존
				Lrotate(pTParent, pSibling);	//이 작업은 추가적인 특성 위반을 일으키지 않는다.
				continue;
			}
			//case 2 : sibling is black and its children's color is black : target change
			if (!pSibling || 
				(getColor(pSibling->left()) == BLACK) && (getColor(pSibling->right()) == BLACK))
			{
				//Sibling 경로의 black을 하나 줄여 target.경로와 동일하게 
				//1개 부족한 경로로 만듦
				setColor(pSibling, RED);

				//부모를 다음 작업 대상으로 지정
				//부모가 RED인 경우 루프를 빠져나가 BLACK으로 변환 되며 A와 B가 해결됨
				//BLACK인 경우 해당 단계에서 다시 루프수행
				pTarget = pTParent;				
				pTParent = pTParent->parent();	 
			}
			//case 3 : sibling is black and sibling's left child is red
			else
			{
				if (getColor(pSibling->left()) == RED)
				{
					setColor(pSibling, RED);
					setColor(pSibling->left(), BLACK);		//부모와 색을 스위치해 A를 보존
					Rrotate(pSibling, pSibling->left());	//이 작업 또한 추가적인 특성 위반을 일으키지 않는다.
					pSibling = pSibling->parent();
				}
				//case 4 (else case) : sibling is black and sibling's right child is red
				setColor(pSibling->right(), BLACK);
				setColor(pSibling, RED);				//Property 5 violation
				pTParent->setColor(BLACK);
				Lrotate(pTParent, pSibling);			//recover property 5

				pTarget = getRoot();
			}
		}
		else //pTarget is its parent's right child
		{
			pSibling = pTParent->left();

			//case 1 : sibling is red => convert one of cases : case 2 or 3 or 4
			if (getColor(pSibling) == RED)
			{
				setColor(pTParent, RED);
				setColor(pSibling, BLACK);
				Rrotate(pTParent, pSibling);
				continue;
			}
			//case 2 : sibling is black and its children's color is black : target change
			if (!pSibling ||
				(getColor(pSibling->left()) == BLACK) && (getColor(pSibling->right()) == BLACK))
			{
				setColor(pSibling, RED);
				pTarget = pTParent;
				pTParent = pTParent->parent();
			}
			//case 3 : sibling is black and sibling's right child is red
			else
			{
				if (getColor(pSibling->right()) == RED)
				{
					setColor(pSibling, RED);
					setColor(pSibling->right(), BLACK);
					Lrotate(pSibling, pSibling->right());
					pSibling = pSibling->parent();
				}
				//case 4 (else case) : sibling is black and sibling's left child is red
				setColor(pSibling->left(), BLACK);
				setColor(pSibling, RED);
				setColor(pTParent, BLACK);
				Rrotate(pTParent, pSibling);

				pTarget = getRoot();
			}
		}
	}

	setColor(pTarget, BLACK);
}
