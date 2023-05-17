#include "mycollision.h"

CollisionType MyCollision::rectToRect(const MyRect& r1, const MyRect& r2)
{
	MyRect unionRect = getUnion2F(r1, r2);

	if (unionRect.fWH.p[0] <= r1.fWH.p[0] + r2.fWH.p[0])
	{
		if (unionRect.fWH.p[1] <= r1.fWH.p[1] + r2.fWH.p[1])
		{
			MyRect intersectionRect = getIntersection2F(r1, r2);

			if (intersectionRect == r1 || intersectionRect == r2) 
			{ 
				return CollisionType::CT_IN; 
			}
			return CollisionType::CT_OVERLAP;
		}
	}

	return CollisionType::CT_OUT;
}

CollisionType MyCollision::cubeToCube(const MyCube& c1, const MyCube& c2)
{
	MyCube unionCube = getUnion3F(c1, c2);

	if (unionCube.fWLH.p[0] <= c1.fWLH.p[0] + c2.fWLH.p[0])
	{
		if (unionCube.fWLH.p[1] <= c1.fWLH.p[1] + c2.fWLH.p[1])
		{
			if (unionCube.fWLH.p[2] <= c1.fWLH.p[2] + c2.fWLH.p[2])
			{
				MyCube intersectionCube = getIntersection3F(c1, c2);

				if (intersectionCube == c1 || intersectionCube == c2)
				{
					return CollisionType::CT_IN;
				}
				return CollisionType::CT_OVERLAP;
			}
		}
	}

	return CollisionType::CT_OUT;
}

CollisionType MyCollision::circleToCircle(const MyCircle& c1, const MyCircle& c2)
{
	float dist = MyVector2F::getDistance2f(c1.cPos, c2.cPos);
	float smallR, bigR;

	if (dist <= c1.radius + c2.radius)
	{
		if (c1.radius < c2.radius) { smallR = c1.radius, bigR = c2.radius; }
		else { smallR = c2.radius, bigR = c1.radius; }

		if (dist <= bigR - smallR) { return CollisionType::CT_IN; }
		return CollisionType::CT_OVERLAP;
	}
	return CollisionType::CT_OUT;
}

CollisionType MyCollision::sphereToSphere(const MySphere& s1, const MySphere& s2)
{
	float dist = MyVector3F::getDistance(s1.cPos, s2.cPos);
	float smallR, bigR;

	if (dist <= s1.radius + s2.radius)
	{
		if (s1.radius < s2.radius) { smallR = s1.radius, bigR = s2.radius; }
		else { smallR = s2.radius, bigR = s1.radius; }

		if (dist <= bigR - smallR) { return CollisionType::CT_IN; }
		return CollisionType::CT_OVERLAP;
	}
	return CollisionType::CT_OUT;
}

MyRect MyCollision::getUnion2F(const MyRect& r1, const MyRect& r2)
{
	float l, r, t, b, w, h;

	l = (r1.pos.x < r2.pos.x) ? r1.pos.x : r2.pos.x;
	r = (r1.pos.x + r1.fWH.p[0] > r2.pos.x + r2.fWH.p[0]) ? r1.pos.x + r1.fWH.p[0] : r2.pos.x + r2.fWH.p[0];

	t = (r1.pos.y < r2.pos.y) ? r1.pos.y : r2.pos.y;
	b = (r1.pos.y + r1.fWH.p[1] > r2.pos.y + r2.fWH.p[1]) ? r1.pos.y + r1.fWH.p[1] : r2.pos.y + r2.fWH.p[1];

	w = r - l;
	h = b - t;

	return MyRect(l, t, w, h);
}

MyCube MyCollision::getUnion3F(const MyCube& c1, const MyCube& c2)
{
	float fw, bw, l, r, t, b, w, len, h;

	bw = (c1.pos.x < c2.pos.x) ? c1.pos.x : c2.pos.x;
	fw = (c1.pos.x + c1.fWLH.p[0] > c2.pos.x + c2.fWLH.p[0]) ? c1.pos.x + c1.fWLH.p[0] : c2.pos.x + c2.fWLH.p[0];

	l = (c1.pos.y < c2.pos.y) ? c1.pos.y : c2.pos.y;
	r = (c1.pos.y + c1.fWLH.p[1] > c2.pos.y + c2.fWLH.p[1]) ? c1.pos.y + c1.fWLH.p[1] : c2.pos.y + c2.fWLH.p[1];

	t = (c1.pos.z < c2.pos.z) ? c1.pos.z : c2.pos.z;
	b = (c1.pos.z + c1.fWLH.p[2] > c2.pos.z + c2.fWLH.p[2]) ? c1.pos.z + c1.fWLH.p[2] : c2.pos.z + c2.fWLH.p[2];

	w = fw - bw;
	len = r - l;
	h = b - t;

	return MyCube(bw, l, t, w, len, h);
}

MyRect MyCollision::getIntersection2F(const MyRect& r1, const MyRect& r2)
{
	float l, r, t, b, w, h;

	l = (r1.pos.x > r2.pos.x) ? r1.pos.x : r2.pos.x;
	r = (r1.pos.x + r1.fWH.p[0] < r2.pos.x + r2.fWH.p[0]) ? r1.pos.x + r1.fWH.p[0] : r2.pos.x + r2.fWH.p[0];

	t = (r1.pos.y > r2.pos.y) ? r1.pos.y : r2.pos.y;
	b = (r1.pos.y + r1.fWH.p[1] < r2.pos.y + r2.fWH.p[1]) ? r1.pos.y + r1.fWH.p[1] : r2.pos.y + r2.fWH.p[1];

	w = r - l;
	h = b - t;
	return MyRect(l, t, w, h);
}

MyCube MyCollision::getIntersection3F(const MyCube& c1, const MyCube& c2)
{
	float fw, bw, l, r, t, b, w, len, h;

	bw = (c1.pos.x > c2.pos.x) ? c1.pos.x : c2.pos.x;
	fw = (c1.pos.x + c1.fWLH.p[0] < c2.pos.x + c2.fWLH.p[0]) ? c1.pos.x + c1.fWLH.p[0] : c2.pos.x + c2.fWLH.p[0];

	l = (c1.pos.y > c2.pos.y) ? c1.pos.y : c2.pos.y;
	r = (c1.pos.y + c1.fWLH.p[1] < c2.pos.y + c2.fWLH.p[1]) ? c1.pos.y + c1.fWLH.p[1] : c2.pos.y + c2.fWLH.p[1];

	t = (c1.pos.z > c2.pos.z) ? c1.pos.z : c2.pos.z;
	b = (c1.pos.z + c1.fWLH.p[2] < c2.pos.z + c2.fWLH.p[2]) ? c1.pos.z + c1.fWLH.p[2] : c2.pos.z + c2.fWLH.p[2];

	w = fw - bw;
	len = r - l;
	h = b - t;

	return MyCube(bw, l, t, w, len, h);
}

