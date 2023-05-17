#pragma once
#include "myobject.h"

class QuadTreeNode
{
public:
	QuadTreeNode* pParent;
	vector<QuadTreeNode*> pChild;
	int depth;
	MyRect nPos;
	vector<MyObject2F*> staticObjList;
	vector<MyDynamicObject2F*> dynamicObjList;

public:
	QuadTreeNode();
	QuadTreeNode(float x, float y, float width, float height, int depth = 0);
	QuadTreeNode(MyVector2F pos, MyVector2F fWH, int depth = 0);
	QuadTreeNode(MyRect nPos, int depth = 0);
	~QuadTreeNode();

	void setNode(float x, float y, float width, float height, int depth = 0);
	void setNode(MyVector2F pos, MyVector2F fWH, int depth = 0);
	void setNode(MyRect nPos, int depth = 0);
};

class OctTreeNode
{
public:
	OctTreeNode* pParent;
	vector<OctTreeNode*> pChild;
	int depth;
	MyCube nPos;
	vector<MyObject3F*> staticObjList;
	vector<MyDynamicObject3F*> dynamicObjList;

public:
	OctTreeNode();
	OctTreeNode(float x, float y, float z, 
		float width, float length, float height, int depth = 0);
	OctTreeNode(MyVector3F pos, MyVector3F fWLH, int depth = 0);
	OctTreeNode(MyCube nPos, int depth = 0);
	~OctTreeNode();

	void setNode(float x, float y, float z,
		float width, float length, float height, int depth = 0);
	void setNode(MyVector3F pos, MyVector3F fWLH, int depth = 0);
	void setNode(MyCube nPos, int depth = 0);
};