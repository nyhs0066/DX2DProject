#include "mycollision.h"

UINT MyCollision::cubeToCube(MyCube& c1, MyCube& c2)
{
	MyCube unionCube = getUnionCube(c1, c2);
	MyCube intersectionCube;

	if (unionCube.fWLH.v[0] <= c1.fWLH.v[0] + c2.fWLH.v[0])
	{
		if (unionCube.fWLH.v[1] <= c1.fWLH.v[1] + c2.fWLH.v[1])
		{
			if (unionCube.fWLH.v[2] <= c1.fWLH.v[2] + c2.fWLH.v[2])
			{
				intersectionCube = getIntersectionCube(c1, c2);

				if (intersectionCube == c1 || intersectionCube == c2) { return MYCT_IN; }
				else { return MYCT_OVERLAP; }
			}
		}
	}

	return MYCT_OUT;
}

MyCube MyCollision::getUnionCube(MyCube& c1, MyCube& c2)
{
	float left, top, right, bottom, front, back;

	(c1.pos.x < c2.pos.x) ? 
		(left = c1.pos.x, right = c2.pos.x + c2.fWLH.v[0]) : (left = c2.pos.x, right = c1.pos.x + c1.fWLH.v[0]);
	(c1.pos.y < c2.pos.y) ?
		(top = c1.pos.y, bottom = c2.pos.y + c2.fWLH.v[1]) : (top = c2.pos.y, bottom = c1.pos.y + c1.fWLH.v[1]);
	(c1.pos.z < c2.pos.z) ?
		(front = c1.pos.z, back = c2.pos.z + c2.fWLH.v[2]) : (front = c2.pos.z, back = c1.pos.z + c1.fWLH.v[2]);

	return MyCube({ {left, top, front}, { right - left, bottom - top, back - front } });
}

MyCube MyCollision::getIntersectionCube(MyCube& c1, MyCube& c2)
{
	float left, top, right, bottom, front, back;

	(c1.pos.x >= c2.pos.x) ?
		(left = c1.pos.x, right = c2.pos.x + c2.fWLH.v[0]) : (left = c2.pos.x, right = c1.pos.x + c1.fWLH.v[0]);
	(c1.pos.y >= c2.pos.y) ?
		(top = c1.pos.y, bottom = c2.pos.y + c2.fWLH.v[1]) : (top = c2.pos.y, bottom = c1.pos.y + c1.fWLH.v[1]);
	(c1.pos.z >= c2.pos.z) ?
		(front = c1.pos.z, back = c2.pos.z + c2.fWLH.v[2]) : (front = c2.pos.z, back = c1.pos.z + c1.fWLH.v[2]);

	return MyCube({ {left, top, front}, { right - left, bottom - top, back - front } });
}

UINT MyCollision::getCollisionPlane(MyCube& dest, MyCube& src, MyVector3F vSrcDirection)
{
	if (vSrcDirection.x > 0.0f && vSrcDirection.y > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWLH.v[0]) + src.pos.y + src.fWLH.v[1];

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWLH.v[1]) { return MYCP_LEFT; }
		else { return MYCP_TOP; }
	}
	else if (vSrcDirection.x > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x - src.pos.x - src.fWLH.v[0]) + src.pos.y;

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWLH.v[1]) { return MYCP_LEFT; }
		else { return MYCP_BOT; }
	}
	else if (vSrcDirection.y > 0.0f)
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWLH.v[0] - src.pos.x) + src.pos.y + src.fWLH.v[1];

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWLH.v[1]) { return MYCP_RIGHT; }
		else { return MYCP_TOP; }
	}
	else
	{
		FLOAT ret = (vSrcDirection.y / vSrcDirection.x) * (dest.pos.x + dest.fWLH.v[0] - src.pos.x) + src.pos.y;

		if (dest.pos.y <= ret && ret <= dest.pos.y + dest.fWLH.v[1]) { return MYCP_RIGHT; }
		else { return MYCP_BOT; }
	}
}
