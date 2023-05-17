#pragma once
#include "myunih.h"
#include "myshape.h"

enum MYCOLLISION_TYPE { MYCT_OUT, MYCT_OVERLAP, MYCT_IN };
enum COLLISION_PLANE { MYCP_NONE, MYCP_TOP, MYCP_BOT, MYCP_LEFT, MYCP_RIGHT};

class MyCollision
{
public:
	static UINT rectToRect(const MyRect& r1, const MyRect& r2);

	static MyRect getUnionRect(const MyRect& r1, const MyRect& r2);
	static MyRect getIntersectionRect(const MyRect& r1, const MyRect& r2);

	static COLLISION_PLANE getCollisionPlane(const MyRect& dest, const MyRect& src, MyVector2F vSrcDirection);
};