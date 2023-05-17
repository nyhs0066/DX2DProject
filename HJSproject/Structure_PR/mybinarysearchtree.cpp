#include "mybinarysearchtree.h"

TNode::TNode()
{
	pParent = pLeft = pRight = nullptr;
}

TNode::TNode(int data) : TNode()
{
	this->data = data;
}

TNode::~TNode()
{
}

int TNode::getData()
{
	return data;
}

void TNode::setData(int set)
{
	data = set;
}

BinarySearchTree::BinarySearchTree()
{
	pRoot = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	clearTree();
}

TNode* BinarySearchTree::createTNode(int data)
{
	TNode* pNewE = new TNode(data);
	assert(pNewE);
	return pNewE;
}

void BinarySearchTree::insertTNode(TNode* pNewE)
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
}

void BinarySearchTree::deleteTNode(TNode* pTarget)
{
	if (pTarget)
	{
		if (!pTarget->pLeft) { transPlant(pTarget, pTarget->pRight); }
		else if (!pTarget->pRight) { transPlant(pTarget, pTarget->pLeft); }
		else
		{
			TNode* temp = getMaximum(pTarget->pLeft);
			if (temp->pParent != pTarget)
			{
				transPlant(temp, temp->pLeft);		//왼쪽 서브트리를 이동할 노드 위치로 이동
				temp->pLeft = pTarget->pLeft;		//이동할 노드의 왼쪽 노드를 삭제할 노드의 왼쪽노드로 지정
				pTarget->pLeft->pParent = temp;		//삭제할 노드 왼쪽 노드의 부모 노드 갱신
			}
			transPlant(pTarget, temp);
			temp->pRight = pTarget->pRight;			//이동할 노드의 오른쪽 노드를 삭제할 노드의 오른쪽 노드로 지정
			pTarget->pRight->pParent = temp;		//삭제할 노드 오른쪽 노드의 부모 노드 갱신
		}

		delete pTarget;
		pTarget = nullptr;
	}
}

TNode* BinarySearchTree::getRoot()
{
	return pRoot;
}

TNode* BinarySearchTree::getSuccessor(TNode* pTarget)
{
	if (pTarget)
	{
		if (pTarget->pRight) { return getMinimum(pTarget->pRight); }
		else 
		{ 
			TNode* trailingPointer = nullptr;

			while (pTarget && trailingPointer == pTarget->pRight)
			{
				trailingPointer = pTarget;
				pTarget = pTarget->pParent;
			}
		}
	}
	
	return pTarget;
}

TNode* BinarySearchTree::getPredecessor(TNode* pTarget)
{
	if (pTarget)
	{
		if (pTarget->pLeft) { return getMaximum(pTarget->pLeft); }
		else
		{
			TNode* trailingPointer = nullptr;

			while (pTarget && trailingPointer == pTarget->pLeft)
			{
				trailingPointer = pTarget;
				pTarget = pTarget->pParent;
			}
		}
	}

	return pTarget;
}

TNode* BinarySearchTree::getMinimum(TNode* pTarget)
{
	if (pTarget)
	{
		while (pTarget->pLeft) { pTarget = pTarget->pLeft; }
	}
	
	return pTarget;
}

TNode* BinarySearchTree::getMaximum(TNode* pTarget)
{
	if (pTarget)
	{
		while (pTarget->pRight) { pTarget = pTarget->pRight; }
	}

	return pTarget;
}

void BinarySearchTree::inOrderTraversal(TNode* pRoot)
{
	TNode* pTarget = getMinimum(pRoot);

	while (pTarget)
	{
		std::cout << pTarget->getData() << ' ';

		//이 if 부분은 getMinimum(pTarget->pRight)와 동치
		if (pTarget->pRight) 
		{ 
			pTarget = pTarget->pRight; 
			while (pTarget->pLeft) { pTarget = pTarget->pLeft; }
		}
		else
		{
			TNode* trailingPointer = nullptr;

			while (pTarget && trailingPointer == pTarget->pRight)
			{
				trailingPointer = pTarget;
				pTarget = pTarget->pParent;
			}
		}
	}

	cout << '\n';

	// 재귀
	/*
	if (!pRoot) { return; }

	inOrderTraversal(pRoot->pLeft);

	std::cout << pRoot->getData();

	inOrderTraversal(pRoot->pRight);
	*/
}

void BinarySearchTree::preOrderTraversal(TNode* pRoot)
{
	if (!pRoot) { return; }

	inOrderTraversal(pRoot->pLeft);

	std::cout << pRoot->getData();

	inOrderTraversal(pRoot->pRight);
}

void BinarySearchTree::levelOrderTraversal(TNode* pRoot)
{
	std::queue<TNode*> Q;
	TNode* cur;
	Q.push(pRoot);

	while (!Q.empty())
	{
		cur = Q.front();
		Q.pop();
		if (cur->pLeft) { Q.push(cur->pLeft); }
		if (cur->pRight) { Q.push(cur->pRight); }
		cout << cur->getData() << ' ';
	}

	cout << '\n';
}

TNode* BinarySearchTree::search(int key)
{
	TNode* cur = pRoot;
	int comp;

	while (cur)
	{
		comp = cur->getData();
		if (comp == key) { break; }
		else if (comp < key) { cur = cur->pLeft; }
		else { cur = cur->pRight; }
	}
	
	return cur;
}

TNode* BinarySearchTree::transPlant(TNode* dest, TNode* source)
{
	//위치 이동할 노드의 연결 상태를 모두 교정한다.
	//source의 자식 노드가 없는 경우만 정상 작동한다.
	if (dest)
	{
		if (!dest->pParent)
		{
			pRoot = source;
			if (source) { source->pParent = nullptr; }
		}
		else if (dest->pParent->pLeft == dest) { dest->pParent->pLeft = source; }
		else { dest->pParent->pRight = source; }

		if (source) { source->pParent = dest->pParent; }
	}

	return dest;
}

void BinarySearchTree::clearTree()
{
	clearTreeSub(pRoot);
}

void BinarySearchTree::clearTreeSub(TNode* pTarget)
{
	if (pTarget)
	{
		clearTreeSub(pTarget->pLeft);
		clearTreeSub(pTarget->pRight);
		delete pTarget;
	}
}


