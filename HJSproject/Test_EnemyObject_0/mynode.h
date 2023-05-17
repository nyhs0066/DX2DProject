#pragma once
#include "myobject2d.h"

class QuadTreeNode
{
public:
	QuadTreeNode* pParent;
	vector<QuadTreeNode*> pChild;
	int depth;
	MyExRect nPos;
	vector<MyObject2D*> staticObjList;
	vector<MyObject2D*> dynamicObjList;

public:
	QuadTreeNode();
	QuadTreeNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth = 0);
	QuadTreeNode(MyVector2F pos, MyVector2F fWH, int depth = 0);
	QuadTreeNode(MyExRect nPos, int depth = 0);
	~QuadTreeNode();

	void setNode(FLOAT x, FLOAT y, FLOAT width, FLOAT height, int depth = 0);
	void setNode(MyVector2F pos, MyVector2F fWH, int depth = 0);
	void setNode(MyExRect nPos, int depth = 0);
};