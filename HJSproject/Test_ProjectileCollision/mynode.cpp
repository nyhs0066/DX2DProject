#include "mynode.h"

QuadTreeNode::QuadTreeNode() : QuadTreeNode(MyRect(0.0f, 0.0f, 0.0f, 0.0f), 0) {}

QuadTreeNode::QuadTreeNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth)
{
	setNode(x, y, width, height, depth);
}

QuadTreeNode::QuadTreeNode(MyVector2F pos, MyVector2F fWH, int depth)
{
	setNode(pos, fWH, depth);
}

QuadTreeNode::QuadTreeNode(MyRect nPos, int depth)
{
	setNode(nPos, depth);
}

QuadTreeNode::~QuadTreeNode() {}

void QuadTreeNode::setNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth)
{
	nPos.pos.x = x;
	nPos.pos.y = y;
	nPos.fWH.v[0] = width;
	nPos.fWH.v[1] = height;
	this->depth = depth;
	pParent = nullptr;
}

void QuadTreeNode::setNode(MyVector2F pos, MyVector2F fWH, int depth)
{
	nPos.pos = pos;
	nPos.fWH = fWH;
	this->depth = depth;
	pParent = nullptr;
}

void QuadTreeNode::setNode(MyRect nPos, int depth)
{
	this->nPos = nPos;
	this->depth = depth;
	pParent = nullptr;
}