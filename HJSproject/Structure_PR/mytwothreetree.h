#pragma once
#include "mybinarysearchtree.h"
#include <stack>

using std::stack;

constexpr int EMPTY = 1281217711;

class TwoThreeNode : private TNode
{
private:
	int data[2];

public:
	TwoThreeNode* pChild[3];

	TwoThreeNode();
	~TwoThreeNode();

	int getData(bool idx);
	void setData(bool idx, int data);
};

class TwoThreeTree : public BinarySearchTree
{
private:
	TwoThreeNode* pRoot;

public:
	TwoThreeTree();
	~TwoThreeTree();

	TwoThreeNode*		getRoot();
	void				insertData(int data);
	void				deleteData(int key);
	TwoThreeNode*		getMinimum(TwoThreeNode* pTarget);
	TwoThreeNode*		getMaximum(TwoThreeNode* pTarget);

	void				inOrderTraversal(TwoThreeNode* pRoot);
	TwoThreeNode*		search(int key);
	TwoThreeNode*		transPlant(TwoThreeNode* dest, TwoThreeNode* source);
	void				clearTree();
};