#pragma once
#include "myobject2d.h"

enum TILE_TYPE { TT_NORMAL, TT_SLOPE };

class MyMapObject : public MyObject2D
{
public:
	MyMapObject();
	~MyMapObject();

	virtual bool addChild(MyMapObject* pMObj);
};

class MyTile : public MyMapObject
{
public:
	MyTile();
	~MyTile();
};

class MyTilePlatform : public MyMapObject
{
public:
	vector<MyMapObject*> m_pChildren;

	MyTilePlatform();
	~MyTilePlatform();

	bool frame() override;
	bool postFrame(const MyRect& camRt, FLOAT radian = 0.0f) override;
	bool render() override;
	bool release() override;

	bool addChild(MyMapObject* pMObj) override;
};
