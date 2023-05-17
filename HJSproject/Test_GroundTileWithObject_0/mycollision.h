#pragma once
#include "myunih.h"
#include "myshape.h"

enum MYCOLLISION_TYPE { MYCT_OUT, MYCT_OVERLAP, MYCT_IN };
enum COLLISION_PLANE { MYCP_NONE, MYCP_TOP, MYCP_BOT, MYCP_LEFT, MYCP_RIGHT};

class MyCollision
{
public:
	static UINT rectToRect(MyRect& c1, MyRect& c2);

	static MyRect getUnionRect(MyRect& c1, MyRect& c2);
	static MyRect getIntersectionRect(MyRect& c1, MyRect& c2);

	static COLLISION_PLANE getCollisionPlane(MyRect& dest, MyRect& src, MyVector2F vSrcDirection);
};