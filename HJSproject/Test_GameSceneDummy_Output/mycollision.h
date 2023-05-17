#pragma once
#include "myunih.h"
#include "myshape.h"

enum MYCOLLISION_TYPE { MYCT_OUT, MYCT_OVERLAP, MYCT_IN };
enum COLLISION_PLANE { MYCP_NONE, MYCP_TOP, MYCP_BOT, MYCP_LEFT, MYCP_RIGHT};

class MyCollision
{
public:
	static MYCOLLISION_TYPE pointToRect(const MyVector2F& pt, const MyExRect& rt);

	static MYCOLLISION_TYPE rectToRect(const MyExRect& r1, const MyExRect& r2, MyExRect* outInst = nullptr);
	static MYCOLLISION_TYPE cubeToCube(const MyCube& c1, const MyCube& c2);
	static MYCOLLISION_TYPE circleToCircle(const MyCircle& c1, const MyCircle& c2);
	static MYCOLLISION_TYPE sphereToSphere(const MySphere& s1, const MySphere& s2);

	static MyExRect getUnion2F(const MyExRect& r1, const MyExRect& r2);
	static MyCube getUnion3F(const MyCube& c1, const MyCube& c2);

	static MyExRect getIntersection2F(const MyExRect& r1, const MyExRect& r2);
	static MyCube getIntersection3F(const MyCube& c1, const MyCube& c2);

	static COLLISION_PLANE getCollisionPlane(const MyExRect& dest, const MyExRect& src, MyVector2F vSrcDirection);
};