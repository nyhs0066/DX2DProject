#include "mycollision.h"

MYCOLLISION_TYPE MyCollision::pointToRect(const MyVector2F& pt, const MyExRect& rt)
{
	if (rt.pos.x <= pt.x && pt.x < rt.pos.x + rt.fWH.x)
	{
		if (rt.pos.y <= pt.y && pt.y < rt.pos.y + rt.fWH.y)
		{
			return MYCT_IN;
		}
	}

	return MYCT_OUT;
}

MYCOLLISION_TYPE MyCollision::rectToRect(const MyExRect& r1, const MyExRect& r2, MyExRect* outInst)
{
	MyExRect unionRect = getUnion2F(r1, r2);

	if (unionRect.fWH.v[0] < r1.fWH.v[0] + r2.fWH.v[0])
	{
		if (unionRect.fWH.v[1] < r1.fWH.v[1] + r2.fWH.v[1])
		{
			MyExRect intersectionRect = getIntersection2F(r1, r2);
			if (outInst) { *outInst = intersectionRect; }

			if (intersectionRect == r1 || intersectionRect == r2)
			{
				return MYCOLLISION_TYPE::MYCT_IN;
			}
			return MYCOLLISION_TYPE::MYCT_OVERLAP;
		}
	}

	return MYCOLLISION_TYPE::MYCT_OUT;
}

MYCOLLISION_TYPE MyCollision::cubeToCube(const MyCube& c1, const MyCube& c2)
{
	MyCube unionCube = getUnion3F(c1, c2);

	if (unionCube.fWLH.v[0] <= c1.fWLH.v[0] + c2.fWLH.v[0])
	{
		if (unionCube.fWLH.v[1] <= c1.fWLH.v[1] + c2.fWLH.v[1])
		{
			if (unionCube.fWLH.v[2] <= c1.fWLH.v[2] + c2.fWLH.v[2])
			{
				MyCube intersectionCube = getIntersection3F(c1, c2);

				if (intersectionCube == c1 || intersectionCube == c2)
				{
					return MYCOLLISION_TYPE::MYCT_IN;
				}
				return MYCOLLISION_TYPE::MYCT_OVERLAP;
			}
		}
	}

	return MYCOLLISION_TYPE::MYCT_OUT;
}

MYCOLLISION_TYPE MyCollision::circleToCircle(const MyCircle& c1, const MyCircle& c2)
{
	FLOAT dist = MyVector2F::getDistance(c1.cPos, c2.cPos);
	FLOAT smallR, bigR;

	if (dist <= c1.radius + c2.radius)
	{
		if (c1.radius < c2.radius) { smallR = c1.radius, bigR = c2.radius; }
		else { smallR = c2.radius, bigR = c1.radius; }

		if (dist <= bigR - smallR) { return MYCOLLISION_TYPE::MYCT_IN; }
		return MYCOLLISION_TYPE::MYCT_OVERLAP;
	}
	return MYCOLLISION_TYPE::MYCT_OUT;
}

MYCOLLISION_TYPE MyCollision::sphereToSphere(const MySphere& s1, const MySphere& s2)
{
	FLOAT dist = MyVector3F::getDistance(s1.cPos, s2.cPos);
	FLOAT smallR, bigR;

	if (dist <= s1.radius + s2.radius)
	{
		if (s1.radius < s2.radius) { smallR = s1.radius, bigR = s2.radius; }
		else { smallR = s2.radius, bigR = s1.radius; }

		if (dist <= bigR - smallR) { return MYCOLLISION_TYPE::MYCT_IN; }
		return MYCOLLISION_TYPE::MYCT_OVERLAP;
	}
	return MYCOLLISION_TYPE::MYCT_OUT;
}

MyExRect MyCollision::getUnion2F(const MyExRect& r1, const MyExRect& r2)
{
	FLOAT l, r, t, b, w, h;

	l = (r1.pos.x < r2.pos.x) ? r1.pos.x : r2.pos.x;
	r = (r1.pos.x + r1.fWH.v[0] > r2.pos.x + r2.fWH.v[0]) ? r1.pos.x + r1.fWH.v[0] : r2.pos.x + r2.fWH.v[0];

	t = (r1.pos.y < r2.pos.y) ? r1.pos.y : r2.pos.y;
	b = (r1.pos.y + r1.fWH.v[1] > r2.pos.y + r2.fWH.v[1]) ? r1.pos.y + r1.fWH.v[1] : r2.pos.y + r2.fWH.v[1];

	w = r - l;
	h = b - t;

	return MyExRect(l, t, w, h);
}

MyCube MyCollision::getUnion3F(const MyCube& c1, const MyCube& c2)
{
	FLOAT fw, bw, l, r, t, b, w, len, h;

	bw = (c1.pos.x < c2.pos.x) ? c1.pos.x : c2.pos.x;
	fw = (c1.pos.x + c1.fWLH.v[0] > c2.pos.x + c2.fWLH.v[0]) ? c1.pos.x + c1.fWLH.v[0] : c2.pos.x + c2.fWLH.v[0];

	l = (c1.pos.y < c2.pos.y) ? c1.pos.y : c2.pos.y;
	r = (c1.pos.y + c1.fWLH.v[1] > c2.pos.y + c2.fWLH.v[1]) ? c1.pos.y + c1.fWLH.v[1] : c2.pos.y + c2.fWLH.v[1];

	t = (c1.pos.z < c2.pos.z) ? c1.pos.z : c2.pos.z;
	b = (c1.pos.z + c1.fWLH.v[2] > c2.pos.z + c2.fWLH.v[2]) ? c1.pos.z + c1.fWLH.v[2] : c2.pos.z + c2.fWLH.v[2];

	w = fw - bw;
	len = r - l;
	h = b - t;

	return MyCube(bw, l, t, w, len, h);
}

MyExRect MyCollision::getIntersection2F(const MyExRect& r1, const MyExRect& r2)
{
	FLOAT l, r, t, b, w, h;

	l = (r1.pos.x > r2.pos.x) ? r1.pos.x : r2.pos.x;
	r = (r1.pos.x + r1.fWH.v[0] < r2.pos.x + r2.fWH.v[0]) ? r1.pos.x + r1.fWH.v[0] : r2.pos.x + r2.fWH.v[0];

	t = (r1.pos.y > r2.pos.y) ? r1.pos.y : r2.pos.y;
	b = (r1.pos.y + r1.fWH.v[1] < r2.pos.y + r2.fWH.v[1]) ? r1.pos.y + r1.fWH.v[1] : r2.pos.y + r2.fWH.v[1];

	w = r - l;
	h = b - t;
	return MyExRect(l, t, w, h);
}

MyCube MyCollision::getIntersection3F(const MyCube& c1, const MyCube& c2)
{
	FLOAT fw, bw, l, r, t, b, w, len, h;

	bw = (c1.pos.x > c2.pos.x) ? c1.pos.x : c2.pos.x;
	fw = (c1.pos.x + c1.fWLH.v[0] < c2.pos.x + c2.fWLH.v[0]) ? c1.pos.x + c1.fWLH.v[0] : c2.pos.x + c2.fWLH.v[0];

	l = (c1.pos.y > c2.pos.y) ? c1.pos.y : c2.pos.y;
	r = (c1.pos.y + c1.fWLH.v[1] < c2.pos.y + c2.fWLH.v[1]) ? c1.pos.y + c1.fWLH.v[1] : c2.pos.y + c2.fWLH.v[1];

	t = (c1.pos.z > c2.pos.z) ? c1.pos.z : c2.pos.z;
	b = (c1.pos.z + c1.fWLH.v[2] < c2.pos.z + c2.fWLH.v[2]) ? c1.pos.z + c1.fWLH.v[2] : c2.pos.z + c2.fWLH.v[2];

	w = fw - bw;
	len = r - l;
	h = b - t;

	return MyCube(bw, l, t, w, len, h);
}

COLLISION_PLANE MyCollision::getCollisionPlane(const MyExRect& dest, const MyExRect& src, const MyVector2F vSrcDirection)
{
	FLOAT ret = 0.0f;

	if (vSrcDirection.x > 0.0f && vSrcDirection.y > 0.0f)
	{
		ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWH.v[0]) + src.pos.y + src.fWH.v[1];

		if (dest.pos.y < ret) { return MYCP_LEFT; }
		else { return MYCP_TOP; }
	}
	else if (vSrcDirection.x > 0.0f)
	{
		ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWH.v[0]) + src.pos.y;

		if (ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_LEFT; }
		else { return MYCP_BOT; }
	}
	else if (vSrcDirection.y > 0.0f)
	{
		if (fabs(vSrcDirection.x) <= MY_MARGIN_OF_ERROR) { return MYCP_TOP; }
		ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWH.v[0] - src.pos.x) + src.pos.y + src.fWH.v[1];

		if (dest.pos.y < ret) { return MYCP_RIGHT; }
		else { return MYCP_TOP; }
	}
	else
	{
		if (fabs(vSrcDirection.x) <= MY_MARGIN_OF_ERROR) { return MYCP_BOT; }

		ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWH.v[0] - src.pos.x) + src.pos.y;

		if (ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_RIGHT; }
		else { return MYCP_BOT; }
	}
}
