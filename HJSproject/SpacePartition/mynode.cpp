#include "mynode.h"

QuadTreeNode::QuadTreeNode() : QuadTreeNode(MyRect(0.0f, 0.0f, 0.0f, 0.0f), 0) {}

QuadTreeNode::QuadTreeNode(float x, float y, float width, float height, int depth)
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

void QuadTreeNode::setNode(float x, float y, float width, float height, int depth)
{
	nPos.pos.x = x;
	nPos.pos.y = y;
	nPos.fWH.p[0] = width;
	nPos.fWH.p[1] = height;
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

OctTreeNode::OctTreeNode() : OctTreeNode(MyCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 0) {}

OctTreeNode::OctTreeNode(float x, float y, float z, 
	float width, float length, float height, int depth)
{
	setNode(x, y, z, width, length, height, depth);
}

OctTreeNode::OctTreeNode(MyVector3F pos, MyVector3F fWLH, int depth)
{
	setNode(pos, fWLH, depth);
}

OctTreeNode::OctTreeNode(MyCube nPos, int depth)
{
	setNode(nPos, depth);
}

OctTreeNode::~OctTreeNode() {}

void OctTreeNode::setNode(float x, float y, float z, float width, float length, float height, int depth)
{
	nPos.pos.x = x;
	nPos.pos.y = y;
	nPos.pos.z = z;
	nPos.fWLH.p[0] = width;
	nPos.fWLH.p[1] = length;
	nPos.fWLH.p[2] = height;
	this->depth = depth;
	pParent = nullptr;
}

void OctTreeNode::setNode(MyVector3F pos, MyVector3F fWLH, int depth)
{
	nPos.pos = pos;
	nPos.fWLH = fWLH;
	this->depth = depth;
	pParent = nullptr;
}

void OctTreeNode::setNode(MyCube nPos, int depth)
{
	this->nPos = nPos;
	this->depth = depth;
	pParent = nullptr;
}
