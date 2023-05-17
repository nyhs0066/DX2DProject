#pragma once
#include "myshape.h"

class MyObject
{
public:
	virtual ~MyObject();

	virtual void frame(const MyShape* boundary, float deltaT, float gameT) = 0;
	virtual void draw() = 0;
};

class MyObject2F : public MyObject
{
public:
	MyVector2F	vDirection;
	MyCircle	posCircle;
	MyRect		posRect;

	MyVector2F	vForcePerSec;
	MyVector2F	vAccelerationPerSec;
	MyVector2F	vVelocity;
	MyVector2F	vFriction;

	float		speedPerSec;
	float		mass;

public:
	MyObject2F();
	MyObject2F(float x, float y, float width, float height);
	MyObject2F(MyVector2F pos, MyVector2F fWH);
	MyObject2F(MyRect rect);
	virtual ~MyObject2F();

	void setPosition(float x, float y);
	void setPosition(MyVector2F pos);
	MyVector2F getPosition();

	void setWH(float width, float height);
	void setWH(MyVector2F fWH);
	MyVector2F getWH();

	void addForce(MyVector2F vF);
	void resetForce();

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;

	virtual MyVector2F calculateDisplacement(float deltaT);
};

class MyDynamicObject2F : public MyObject2F
{
public:
	MyDynamicObject2F();
	MyDynamicObject2F(float x, float y, float width, float height);
	MyDynamicObject2F(MyVector2F pos, MyVector2F fWH);
	MyDynamicObject2F(MyRect rect);

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;
};

class MyObject3F : public MyObject
{
public:
	MyVector3F	vDirection;
	MySphere	posSphere;
	MyCube		posCube;

	MyVector3F	vForcePerSec;
	MyVector3F	vAccelerationPerSec;
	MyVector3F	vVelocity;
	MyVector3F	vFriction;

	float		speedPerSec;
	float		mass;

public:
	MyObject3F();
	MyObject3F(float x, float y, float z, float width, float length, float height);
	MyObject3F(MyVector3F pos, MyVector3F fWLH);
	MyObject3F(MyCube cube);
	virtual ~MyObject3F();

	void setPosition(float x, float y, float z);
	void setPosition(MyVector3F pos);
	MyVector3F getPosition();

	void setWLH(float width, float length, float height);
	void setWLH(MyVector3F fWLH);
	MyVector3F getWLH();

	void addForce(MyVector3F vF);
	void resetForce();

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;

	virtual MyVector3F calculateDisplacement(float deltaT);
};

class MyDynamicObject3F : public MyObject3F
{
public:
	MyDynamicObject3F();
	MyDynamicObject3F(float x, float y, float z, float width, float length, float height);
	MyDynamicObject3F(MyVector3F pos, MyVector3F fWLH);
	MyDynamicObject3F(MyCube cube);

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;
};