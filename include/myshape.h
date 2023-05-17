#pragma once
#include "myunih.h"

struct MyShape
{
	virtual ~MyShape();
};

struct MyCircle : MyShape
{
	MyVector2F cPos;
	FLOAT radius;

public:
	MyCircle();
	MyCircle(FLOAT cx, FLOAT cy, FLOAT r);
	MyCircle(MyVector2F cPos, FLOAT r);
	MyCircle(MyVector2F cPos, MyVector2F pt);
	MyCircle(const MyCircle& C);

	void set(FLOAT cx, FLOAT cy, FLOAT r);
	void set(MyVector2F cPos, FLOAT r);
	void set(const MyCircle& C);
	void set(MyVector2F cPos, MyVector2F pt);

	bool operator==(const MyCircle& opd);
	bool operator!=(const MyCircle& opd);
};

struct MyRect : MyShape
{
	union
	{
		FLOAT v[4];
		struct
		{
			MyVector2F pos;
			MyVector2F fWH;
		};
		MyVector4F rt;
	};

public:
	MyRect();
	MyRect(FLOAT x, FLOAT y, FLOAT w, FLOAT h);
	MyRect(MyVector2F pos, MyVector2F fWH);
	MyRect(MyVector4F rt);
	MyRect(const MyRect& rt);

	void set(FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	void set(MyVector2F pos, MyVector2F fWH);
	void set(MyVector4F rt);
	void set(const MyRect& rt);

	MyVector2F getCpos();
	MyVector2F getRBPos();

	bool operator==(const MyRect& opd);
	bool operator!=(const MyRect& opd);
};

struct MySphere : MyShape
{
	MyVector3F cPos;
	FLOAT radius;

public:
	MySphere();
	MySphere(FLOAT cx, FLOAT cy, FLOAT cz, FLOAT r);
	MySphere(MyVector3F cPos, FLOAT r);
	MySphere(const MySphere& C);
	MySphere(MyVector3F cPos, MyVector3F pt);

	void set(FLOAT cx, FLOAT cy, FLOAT cz, FLOAT r);
	void set(MyVector3F cPos, FLOAT r);
	void set(const MySphere& C);
	void set(MyVector3F cPos, MyVector3F pt);

	bool operator==(const MySphere& opd);
	bool operator!=(const MySphere& opd);
};

struct MyCube : MyShape
{
	union
	{
		FLOAT v[6];
		struct
		{
			MyVector3F pos;
			MyVector3F fWLH;
		};
	};

public:
	MyCube();
	MyCube(FLOAT x, FLOAT y, FLOAT z, FLOAT width, FLOAT length, FLOAT height);
	MyCube(MyVector3F pos, MyVector3F fWLH);
	MyCube(const MyCube& R);

	void set(FLOAT x, FLOAT y, FLOAT z, FLOAT width, FLOAT length, FLOAT height);
	void set(MyVector3F pos, MyVector3F fWLH);
	void set(const MyCube& R);

	MyVector3F getCpos();
	MyVector3F getRBPos();

	bool operator==(const MyCube& opd);
	bool operator!=(const MyCube& opd);
};