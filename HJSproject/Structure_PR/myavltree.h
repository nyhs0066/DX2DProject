#pragma once
#include "mybinarysearchtree.h"

class AVLTNode : public TNode
{
private:
	int height;

public:
	AVLTNode();
	AVLTNode(int data);
	virtual ~AVLTNode();

	int getHeight();
	void setHeight(int H);

	AVLTNode* left();
	AVLTNode* right();
	AVLTNode* parent();
};

class AVLTree : public BinarySearchTree
{
public:
	AVLTree();
	~AVLTree();

	AVLTNode*				createTNode(int data);
	AVLTNode*				getRoot();
	void					insertTNode(AVLTNode* pNewE);
	void					deleteTNode(AVLTNode* pTarget);

private :
	void LLrotate(AVLTNode* A, AVLTNode* B);
	void RRrotate(AVLTNode* A, AVLTNode* B);
	void LRrotate(AVLTNode* A, AVLTNode* B, AVLTNode* C);
	void RLrotate(AVLTNode* A, AVLTNode* B, AVLTNode* C);

	void rebalance(AVLTNode* pCur);
	int factorCheck(AVLTNode* pTarget);
	void resetHeight(AVLTNode* pTarget);
};