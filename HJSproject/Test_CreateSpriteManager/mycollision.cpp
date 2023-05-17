#include "mycollision.h"

UINT MyCollision::rectToRect(const MyRect& r1, const MyRect& r2)
{
	MyRect unionRect = getUnionRect(r1, r2);
	MyRect intersectionRect;

	if (unionRect.fWH.v[0] <= r1.fWH.v[0] + r2.fWH.v[0])
	{
		if (unionRect.fWH.v[1] <= r1.fWH.v[1] + r2.fWH.v[1])
		{
			intersectionRect = getIntersectionRect(r1, r2);

			if (intersectionRect == r1 || intersectionRect == r2) { return MYCT_IN; }
			else { return MYCT_OVERLAP; }
		}
	}

	return MYCT_OUT;
}

MyRect MyCollision::getUnionRect(const MyRect& r1, const MyRect& r2)
{
	float left, top, right, bottom;

	(r1.pos.x < r2.pos.x) ? 
		(left = r1.pos.x, right = r2.pos.x + r2.fWH.v[0]) : (left = r2.pos.x, right = r1.pos.x + r1.fWH.v[0]);
	(r1.pos.y < r2.pos.y) ?
		(top = r1.pos.y, bottom = r2.pos.y + r2.fWH.v[1]) : (top = r2.pos.y, bottom = r1.pos.y + r1.fWH.v[1]);

	return MyRect({ {left, top}, { right - left, bottom - top } });
}

MyRect MyCollision::getIntersectionRect(const MyRect& r1, const MyRect& r2)
{
	float left, top, right, bottom;

	(r1.pos.x >= r2.pos.x) ?
		(left = r1.pos.x, right = r2.pos.x + r2.fWH.v[0]) : (left = r2.pos.x, right = r1.pos.x + r1.fWH.v[0]);
	(r1.pos.y >= r2.pos.y) ?
		(top = r1.pos.y, bottom = r2.pos.y + r2.fWH.v[1]) : (top = r2.pos.y, bottom = r1.pos.y + r1.fWH.v[1]);

	return MyRect({ {left, top}, { right - left, bottom - top } });
}

COLLISION_PLANE MyCollision::getCollisionPlane(const MyRect& dest, const MyRect& src, const MyVector2F vSrcDirection)
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
