#pragma once
#include "myobject2d.h"

enum TILE_TYPE { TT_NORMAL, TT_SLOPE };

class MyMapObject2D : public MyObject2D
{
public:
	MyMapObject2D();
	virtual ~MyMapObject2D();
};

class MyTile2D : public MyMapObject2D
{
public:
	MyTile2D();
	~MyTile2D();
};

class MyTilePlatform2D : public MyMapObject2D
{
public:
	vector<MyMapObject2D*> m_mapObjList;

	MyTilePlatform2D();
	~MyTilePlatform2D();

	bool frame() override;
	bool postFrame(const MyRect& camRt) override;
	bool render() override;
	bool release() override;
};