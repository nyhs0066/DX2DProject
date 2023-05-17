#pragma once
#include <assert.h>
#include "myST.h"
#include <queue>

class TNode
{
private:
	int data;

public:
	TNode* pParent;
	TNode* pLeft;
	TNode* pRight;

	TNode();
	TNode(int data);
	virtual ~TNode();

	int getData();
	void setData(int set);
};

class BinarySearchTree
{
protected:
	TNode* pRoot;

public:
	BinarySearchTree();
	~BinarySearchTree();

	TNode*				createTNode(int data);
	TNode*				getRoot();
	void				insertTNode(TNode* pNewE);
	void				deleteTNode(TNode* pTarget);
	TNode*				getSuccessor(TNode* pTarget);
	TNode*				getPredecessor(TNode* pTarget);
	TNode*				getMinimum(TNode* pTarget);
	TNode*				getMaximum(TNode* pTarget);

	void				inOrderTraversal(TNode* pRoot);
	void				preOrderTraversal(TNode* pRoot);
	void				levelOrderTraversal(TNode* pRoot);
	TNode*				search(int key);
	TNode*				transPlant(TNode* dest, TNode* source);

	void				clearTree();
	void				clearTreeSub(TNode* pTarget);
};