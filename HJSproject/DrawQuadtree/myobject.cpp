#include "myobject.h"

MyObject::~MyObject() {}

MyObject2F::MyObject2F()
{
	mass = 1.0f;
	speedPerSec = 0.0f;
}

MyObject2F::MyObject2F(float x, float y, float width, float height)
{
	posRect.set(x, y, width, height);
	posCircle.cPos = posRect.getCTPoint();
	posCircle.radius = MyVector2F::getDistance2f(posRect.pos, posCircle.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject2F::MyObject2F(MyVector2F pos, MyVector2F fWH)
{
	posRect.set(pos, fWH);
	posCircle.cPos = posRect.getCTPoint();
	posCircle.radius = MyVector2F::getDistance2f(posRect.pos, posCircle.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject2F::MyObject2F(MyRect rect)
{
	posRect = rect;
	posCircle.cPos = posRect.getCTPoint();
	posCircle.radius = MyVector2F::getDistance2f(posRect.pos, posCircle.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject2F::~MyObject2F() {}

void MyObject2F::setPosition(float x, float y)
{
	posRect.pos.x = x;
	posRect.pos.y = y;
	posCircle.cPos = posRect.getCTPoint();
}

void MyObject2F::setPosition(MyVector2F pos)
{
	posRect.pos = pos;
	posCircle.cPos = posRect.getCTPoint();
}

MyVector2F MyObject2F::getPosition()
{
	return posRect.pos;
}

void MyObject2F::setWH(float width, float height)
{
	posRect.fWH.p[0] = width;
	posRect.fWH.p[1] = height;
	posCircle.cPos = posRect.getCTPoint();
	posCircle.radius = MyVector2F::getDistance2f(posRect.pos, posCircle.cPos);
}

void MyObject2F::setWH(MyVector2F fWH)
{
	posRect.fWH = fWH;
	posCircle.cPos = posRect.getCTPoint();
	posCircle.radius = MyVector2F::getDistance2f(posRect.pos, posCircle.cPos);
}

MyVector2F MyObject2F::getWH()
{
	return posRect.fWH;
}

void MyObject2F::addForce(MyVector2F vF)
{
	float inverseMass = 1.0f / mass;

	vForcePerSec += vF;
	vDirection = vForcePerSec.getIdentity();
	speedPerSec = vForcePerSec.length();
}

void MyObject2F::resetForce()
{
	vForcePerSec.x = 0.0f;
	vForcePerSec.y = 0.0f;
}

void MyObject2F::frame(const MyShape* boundary, float deltaT, float gameT) {}

void MyObject2F::draw()
{
	std::cout << "Static Object : [x] " << posRect.pos.x
		<< " [y] " << posRect.pos.y
		<< " [w] " << posRect.fWH.p[0]
		<< " [h] " << posRect.fWH.p[1] << '\n';
}

MyVector2F MyObject2F::calculateDisplacement(float deltaT)
{
	vAccelerationPerSec = vForcePerSec * (1.0f / mass);
	MyVector2F vPos = vVelocity * deltaT + vAccelerationPerSec * deltaT * (deltaT / 2);
	vVelocity += vAccelerationPerSec * deltaT;
	return vPos;
}

MyDynamicObject2F::MyDynamicObject2F() : MyObject2F(0.0f, 0.0f, 0.0f, 0.0f) {}

MyDynamicObject2F::MyDynamicObject2F(float x, float y, float width, float height)
	: MyObject2F(x, y, width, height) {}

MyDynamicObject2F::MyDynamicObject2F(MyVector2F pos, MyVector2F fWH)
	: MyObject2F(pos, fWH) {}

MyDynamicObject2F::MyDynamicObject2F(MyRect rect)
	: MyObject2F(rect) {}

//부딫히면 가속도/속도 초기화, 힘방향 변경
void MyDynamicObject2F::frame(const MyShape* boundary, float deltaT, float gameT)
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
			resetForce();
			addForce(vNewF);
		}

		setPosition(vPos);
	}
}

void MyDynamicObject2F::draw()
{
	std::cout << "Dynamic Object : [x] " << posRect.pos.x
		<< " [y] " << posRect.pos.y
		<< " [w] " << posRect.fWH.p[0]
		<< " [h] " << posRect.fWH.p[1] << '\n';
}

MyObject3F::MyObject3F()
{
	mass = 1.0f;
	speedPerSec = 0.0f;
}

MyObject3F::MyObject3F(float x, float y, float z, float width, float length, float height)
{
	posCube.set(x, y, z, width, length, height);
	posSphere.cPos = posCube.getCTPoint();
	posSphere.radius = MyVector3F::getDistance(posCube.pos, posSphere.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject3F::MyObject3F(MyVector3F pos, MyVector3F fWLH)
{
	posCube.set(pos, fWLH);
	posSphere.cPos = posCube.getCTPoint();
	posSphere.radius = MyVector3F::getDistance(posCube.pos, posSphere.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject3F::MyObject3F(MyCube cube)
{
	posCube = cube;
	posSphere.cPos = posCube.getCTPoint();
	posSphere.radius = MyVector3F::getDistance(posCube.pos, posSphere.cPos);

	speedPerSec = 0.0f;
	mass = 1.0f;
}

MyObject3F::~MyObject3F() {}

void MyObject3F::setPosition(float x, float y, float z)
{
	posCube.pos.x = x;
	posCube.pos.y = y;
	posCube.pos.z = z;
	posSphere.cPos = posCube.getCTPoint();
}

void MyObject3F::setPosition(MyVector3F pos)
{
	posCube.pos = pos;
	posSphere.cPos = posCube.getCTPoint();
}

MyVector3F MyObject3F::getPosition()
{
	return posCube.pos;
}

void MyObject3F::setWLH(float width, float length, float height)
{
	posCube.fWLH.p[0] = width;
	posCube.fWLH.p[1] = length;
	posCube.fWLH.p[2] = height;
	posSphere.cPos = posCube.getCTPoint();
	posSphere.radius = MyVector3F::getDistance(posCube.pos, posSphere.cPos);
}

void MyObject3F::setWLH(MyVector3F fWLH)
{
	posCube.fWLH = fWLH;
	posSphere.cPos = posCube.getCTPoint();
	posSphere.radius = MyVector3F::getDistance(posCube.pos, posSphere.cPos);
}

MyVector3F MyObject3F::getWLH()
{
	return posCube.fWLH;
}

void MyObject3F::addForce(MyVector3F vF)
{
	float inverseMass = 1.0f / mass;

	vForcePerSec += vF;
	vDirection = vForcePerSec.getIdentity();
	speedPerSec = vForcePerSec.length();
}

void MyObject3F::resetForce()
{
	vForcePerSec.x = 0.0f;
	vForcePerSec.y = 0.0f;
	vForcePerSec.z = 0.0f;
}

void MyObject3F::frame(const MyShape* boundary, float deltaT, float gameT) {}

void MyObject3F::draw() 
{
	std::cout << "static Object : [x] " << posCube.pos.x
		<< " [y] " << posCube.pos.y
		<< " [z] " << posCube.pos.z
		<< " [w] " << posCube.fWLH.p[0]
		<< " [l] " << posCube.fWLH.p[1]
		<< " [h] " << posCube.fWLH.p[2] << '\n';
}

MyVector3F MyObject3F::calculateDisplacement(float deltaT)
{
	vAccelerationPerSec = vForcePerSec * (1.0f / mass);
	MyVector3F vPos = vVelocity * deltaT + vAccelerationPerSec * deltaT * (deltaT / 2);
	vVelocity += vAccelerationPerSec * deltaT;
	return vPos;
}

MyDynamicObject3F::MyDynamicObject3F()
	: MyObject3F(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {}

MyDynamicObject3F::MyDynamicObject3F(float x, float y, float z, float width, float length, float height)
	: MyObject3F(x, y, z, width, length, height) {}

MyDynamicObject3F::MyDynamicObject3F(MyVector3F pos, MyVector3F fWLH)
	: MyObject3F(pos, fWLH) {}

MyDynamicObject3F::MyDynamicObject3F(MyCube cube)
	: MyObject3F(cube) {}

void MyDynamicObject3F::frame(const MyShape* boundary, float deltaT, float gameT)
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

void MyDynamicObject3F::draw()
{
	std::cout << "Dynamic Object : [x] " << posCube.pos.x
		<< " [y] " << posCube.pos.y
		<< " [z] " << posCube.pos.z
		<< " [w] " << posCube.fWLH.p[0]
		<< " [l] " << posCube.fWLH.p[1]
		<< " [h] " << posCube.fWLH.p[2] << '\n';
}
