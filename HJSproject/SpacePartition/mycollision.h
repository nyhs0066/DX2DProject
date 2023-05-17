#pragma once
#include "myspacepartition.h"

enum CollisionType { CT_OUT = 0, CT_IN, CT_OVERLAP };

class MyCollision
{
public:
	static CollisionType rectToRect(const MyRect& r1, const MyRect& r2);
	static CollisionType cubeToCube(const MyCube& c1, const MyCube& c2);
	static CollisionType circleToCircle(const MyCircle& c1, const MyCircle& c2);
	static CollisionType sphereToSphere(const MySphere& s1, const MySphere& s2);

	static MyRect getUnion2F(const MyRect& r1, const MyRect& r2);
	static MyCube getUnion3F(const MyCube& c1, const MyCube& c2);

	static MyRect getIntersection2F(const MyRect& r1, const MyRect& r2);
	static MyCube getIntersection3F(const MyCube& c1, const MyCube& c2);
};