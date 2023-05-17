#pragma once
#include "myunih.h"
#include "mybaseobject.h"

enum MYCOLLISION_TYPE { MYCT_OUT, MYCT_OVERLAP, MYCT_IN };
enum COLLISION_PLANE {MYCP_TOP, MYCP_BOT, MYCP_LEFT, MYCP_RIGHT};

class MyCollision
{
public:
	static UINT cubeToCube(MyCube& c1, MyCube& c2);

	static MyCube getUnionCube(MyCube& c1, MyCube& c2);
	static MyCube getIntersectionCube(MyCube& c1, MyCube& c2);

	static UINT getCollisionPlane(MyCube& dest, MyCube& src, MyVector3F vSrcDirection);
};