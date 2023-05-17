#pragma once
#include "myunih.h"
#include "myshape.h"

enum MYCOLLISION_TYPE { MYCT_OUT, MYCT_OVERLAP, MYCT_IN };
enum COLLISION_PLANE { MYCP_NONE, MYCP_TOP, MYCP_BOT, MYCP_LEFT, MYCP_RIGHT};

class MyCollision
{
public:
	static MYCOLLISION_TYPE rectToRect(const MyRect& r1, const MyRect& r2, MyRect* outInst = nullptr);
	static MYCOLLISION_TYPE cubeToCube(const MyCube& c1, const MyCube& c2);
	static MYCOLLISION_TYPE circleToCircle(const MyCircle& c1, const MyCircle& c2);
	static MYCOLLISION_TYPE sphereToSphere(const MySphere& s1, const MySphere& s2);

	static MyRect getUnion2F(const MyRect& r1, const MyRect& r2);
	static MyCube getUnion3F(const MyCube& c1, const MyCube& c2);

	static MyRect getIntersection2F(const MyRect& r1, const MyRect& r2);
	static MyCube getIntersection3F(const MyCube& c1, const MyCube& c2);

	static COLLISION_PLANE getCollisionPlane(const MyRect& dest, const MyRect& src, MyVector2F vSrcDirection);
};