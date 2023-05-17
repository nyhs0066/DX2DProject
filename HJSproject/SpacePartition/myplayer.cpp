#include "myplayer.h"

Player2F::Player2F() : MyObject2F(0.0f, 0.0f, 0.0f, 0.0f) {}

Player2F::Player2F(float x, float y, float width, float height)
	: MyObject2F(x, y, width, height) {}

Player2F::Player2F(MyVector2F pos, MyVector2F fWH)
	: MyObject2F(pos, fWH) {}

Player2F::Player2F(MyRect rect)
	: MyObject2F(rect) {}

void Player2F::frame(const MyShape* boundary, float deltaT, float gameT)
{
	const MyRect* pRect = dynamic_cast<const MyRect*>(boundary);
	if (pRect)
	{
		MyVector2F vPos = getPosition();
		MyVector2F vNewF = vForcePerSec;
		bool flag = false;

		vPos += calculateDisplacement(deltaT);

		MyVector2F bp1 = pRect->pos;
		MyVector2F bp2 = pRect->getRBPoint();

		//left, right, top, bottom
		float limit[4] = { bp1.x, bp2.x - posRect.fWH.p[0],
							bp1.y, bp2.y - posRect.fWH.p[1] };

		if (vPos.x < limit[0]) {
			vPos.x = limit[0];
			flag = true;
			vNewF.x = -vNewF.x;
			vVelocity = MyVector2F(0.0f, vVelocity.y);
		}
		if (vPos.x > limit[1])
		{
			vPos.x = limit[1];
			flag = true;
			vNewF.x = -vNewF.x;
			vVelocity = MyVector2F(0.0f, vVelocity.y);
		}
		if (vPos.y < limit[2])
		{
			vPos.y = limit[2];
			flag = true;
			vNewF.y = -vNewF.y;
			vVelocity = MyVector2F(vVelocity.x, 0.0f);
		}
		if (vPos.y > limit[3])
		{
			vPos.y = limit[3];
			flag = true;
			vNewF.y = -vNewF.y;
			vVelocity = MyVector2F(vVelocity.x, 0.0f);
		}

		if (flag)
		{
			addForce(-vForcePerSec);
			addForce(vNewF);
		}

		setPosition(vPos);
	}
}

void Player2F::draw()
{
	std::cout << "Player2F : [x] " << posRect.pos.x
		<< " [y] " << posRect.pos.y
		<< " [w] " << posRect.fWH.p[0]
		<< " [h] " << posRect.fWH.p[1] << '\n';
}

Player3F::Player3F() : MyObject3F(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {}

Player3F::Player3F(float x, float y, float z, float width, float length, float height)
	: MyObject3F(x, y, z, width, length, height) {}

Player3F::Player3F(MyVector3F pos, MyVector3F fWLH)
	: MyObject3F(pos, fWLH) {}

Player3F::Player3F(MyCube cube)
	: MyObject3F(cube) {}

void Player3F::frame(const MyShape* boundary, float deltaT, float gameT)
{
	const MyCube* pCube = dynamic_cast<const MyCube*>(boundary);
	if (pCube)
	{
		MyVector3F vPos = getPosition();
		MyVector3F temp = vForcePerSec;
		bool flag = false;

		vPos += calculateDisplacement(deltaT);

		MyVector3F bp1 = pCube->pos;
		MyVector3F bp2 = pCube->getFRBPoint();

		//rear, front, left, right, top, bottom
		float limit[6] = { bp1.x, bp2.x - posCube.fWLH.p[0],
							bp1.y, bp2.y - posCube.fWLH.p[1],
							bp1.z, bp2.z - posCube.fWLH.p[2] };

		if (vPos.x < limit[0]) {
			vPos.x = limit[0];
			flag = true;
			temp.x = -temp.x;
			vVelocity = MyVector3F(0.0f, vVelocity.y, vVelocity.z);
		}
		if (vPos.x > limit[1])
		{
			vPos.x = limit[1];
			flag = true;
			temp.x = -temp.x;
			vVelocity = MyVector3F(0.0f, vVelocity.y, vVelocity.z);
		}
		if (vPos.y < limit[2])
		{
			vPos.y = limit[2];
			flag = true;
			temp.y = -temp.y;
			vVelocity = MyVector3F(vVelocity.x, 0.0f, vVelocity.z);
		}
		if (vPos.y > limit[3])
		{
			vPos.y = limit[3];
			flag = true;
			temp.y = -temp.y;
			vVelocity = MyVector3F(vVelocity.x, 0.0f, vVelocity.z);
		}
		if (vPos.z < limit[4])
		{
			vPos.z = limit[4];
			flag = true;
			temp.z = -temp.z;
			vVelocity = MyVector3F(vVelocity.x, vVelocity.y, 0.0f);
		}
		if (vPos.z > limit[5])
		{
			vPos.z = limit[5];
			flag = true;
			temp.z = -temp.z;
			vVelocity = MyVector3F(vVelocity.x, vVelocity.y, 0.0f);
		}

		if (flag)
		{
			resetForce();
			addForce(temp);
		}

		setPosition(vPos);
	}
}

void Player3F::draw()
{
	std::cout << "Player3F : [x] " << posCube.pos.x
		<< " [y] " << posCube.pos.y
		<< " [z] " << posCube.pos.z
		<< " [w] " << posCube.fWLH.p[0]
		<< " [l] " << posCube.fWLH.p[1]
		<< " [h] " << posCube.fWLH.p[2] << '\n';
}
