#include "mycollision.h"

UINT MyCollision::rectToRect(MyRect& c1, MyRect& c2)
{
	MyRect unionRect = getUnionRect(c1, c2);
	MyRect intersectionRect;

	if (unionRect.fWH.v[0] <= c1.fWH.v[0] + c2.fWH.v[0])
	{
		if (unionRect.fWH.v[1] <= c1.fWH.v[1] + c2.fWH.v[1])
		{
			intersectionRect = getIntersectionRect(c1, c2);

			if (intersectionRect == c1 || intersectionRect == c2) { return MYCT_IN; }
			else { return MYCT_OVERLAP; }
		}
	}

	return MYCT_OUT;
}

MyRect MyCollision::getUnionRect(MyRect& c1, MyRect& c2)
{
	float left, top, right, bottom;

	(c1.pos.x < c2.pos.x) ? 
		(left = c1.pos.x, right = c2.pos.x + c2.fWH.v[0]) : (left = c2.pos.x, right = c1.pos.x + c1.fWH.v[0]);
	(c1.pos.y < c2.pos.y) ?
		(top = c1.pos.y, bottom = c2.pos.y + c2.fWH.v[1]) : (top = c2.pos.y, bottom = c1.pos.y + c1.fWH.v[1]);

	return MyRect({ {left, top}, { right - left, bottom - top } });
}

MyRect MyCollision::getIntersectionRect(MyRect& c1, MyRect& c2)
{
	float left, top, right, bottom;

	(c1.pos.x >= c2.pos.x) ?
		(left = c1.pos.x, right = c2.pos.x + c2.fWH.v[0]) : (left = c2.pos.x, right = c1.pos.x + c1.fWH.v[0]);
	(c1.pos.y >= c2.pos.y) ?
		(top = c1.pos.y, bottom = c2.pos.y + c2.fWH.v[1]) : (top = c2.pos.y, bottom = c1.pos.y + c1.fWH.v[1]);

	return MyRect({ {left, top}, { right - left, bottom - top } });
}

UINT MyCollision::getCollisionPlane(MyRect& dest, MyRect& src, MyVector2F vSrcDirection)
{
	if (vSrcDirection.x > 0.0f && vSrcDirection.y > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWH.v[0]) + src.pos.y + src.fWH.v[1];

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_LEFT; }
		else { return MYCP_TOP; }
	}
	else if (vSrcDirection.x > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWH.v[0]) + src.pos.y;

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_LEFT; }
		else { return MYCP_BOT; }
	}
	else if (vSrcDirection.y > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWH.v[0] - src.pos.x) + src.pos.y + src.fWH.v[1];

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_RIGHT; }
		else { return MYCP_TOP; }
	}
	else
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWH.v[0] - src.pos.x) + src.pos.y;

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWH.v[1]) { return MYCP_RIGHT; }
		else { return MYCP_BOT; }
	}
}
