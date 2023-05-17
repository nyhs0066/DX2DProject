#pragma once
#include "myvector.h"

struct MyShape
{
	virtual ~MyShape();
};

struct MyCircle : MyShape
{
	MyVector2F cPos;
	float radius;

public:
	MyCircle();
	MyCircle(float cx, float cy, float r);
	MyCircle(MyVector2F cPos, float r);
	MyCircle(MyVector2F cPos, MyVector2F pt);
	MyCircle(const MyCircle& C);

	void set(float cx, float cy, float r);
	void set(MyVector2F cPos, float r);
	void set(const MyCircle& C);
	void set(MyVector2F cPos, MyVector2F pt);

	bool operator==(const MyCircle& opd);
	bool operator!=(const MyCircle& opd);
};

struct MyRect : MyShape
{
	MyVector2F pos;
	MyVector2F fWH;

public:
	MyRect();
	MyRect(float x, float y, float width, float height);
	MyRect(MyVector2F pos, MyVector2F fWH);
	MyRect(const MyRect& R);

	void set(float x, float y, float width, float height);
	void set(MyVector2F pos, MyVector2F fWH);
	void set(const MyRect& R);

	//Center
	MyVector2F getCTPoint() const;
	//Right - Bottom
	MyVector2F getRBPoint() const;

	bool operator==(const MyRect& opd);
	bool operator!=(const MyRect& opd);
};

struct MySphere : MyShape
{
	MyVector3F cPos;
	float radius;

public:
	MySphere();
	MySphere(float cx, float cy, float cz, float r);
	MySphere(MyVector3F cPos, float r);
	MySphere(const MySphere& C);
	MySphere(MyVector3F cPos, MyVector3F pt);

	void set(float cx, float cy, float cz, float r);
	void set(MyVector3F cPos, float r);
	void set(const MySphere& C);
	void set(MyVector3F cPos, MyVector3F pt);

	bool operator==(const MySphere& opd);
	bool operator!=(const MySphere& opd);
};

struct MyCube : MyShape
{
	MyVector3F pos;
	MyVector3F fWLH;

public:
	MyCube();
	MyCube(float x, float y, float z, float width, float length, float height);
	MyCube(MyVector3F pos, MyVector3F fWLH);
	MyCube(const MyCube& R);

	void set(float x, float y, float z, float width, float length, float height);
	void set(MyVector3F pos, MyVector3F fWLH);
	void set(const MyCube& R);

	//Center
	MyVector3F getCTPoint() const;
	//Front - Right - Bottom
	MyVector3F getFRBPoint() const;

	bool operator==(const MyCube& opd);
	bool operator!=(const MyCube& opd);
};