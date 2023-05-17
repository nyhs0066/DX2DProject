#pragma once
#include "mybinarysearchtree.h"

enum COLOR {RED, BLACK};

class RBTNode : public TNode
{
private:
	//0 = RED, 1 = BLACK 
	bool color;

public:
	RBTNode();
	~RBTNode();

	void setColor(bool color);
	bool getColor();

	RBTNode* left();
	RBTNode* right();
	RBTNode* parent();
};

//Property 1 : Every node is either red or black
//Property 2 : Root is black
//Property 3 : Every leaf is black
//Property 4 : Children of red Node must be black
//Property 5 : For each node, All downward simple paths from itself to descendant leaves have
//				same number of black nodes
class RedBlackTree : public BinarySearchTree 
{
public:
	RedBlackTree();
	~RedBlackTree();

	RBTNode*			createTNode(int data);
	RBTNode*			getRoot();
	void				insertTNode(RBTNode* pNewE);
	void				deleteTNode(RBTNode* pTarget);
	bool				getColor(RBTNode* pTarget);
	void				setColor(RBTNode* pTarget, bool color);

private:
	void Lrotate(RBTNode* A, RBTNode* B);
	void Rrotate(RBTNode* A, RBTNode* B);

	void insertFix(RBTNode* pTarget);
	void deleteFix(RBTNode* pTarget, RBTNode* pTParent);
};