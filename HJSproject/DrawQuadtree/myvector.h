#pragma once
#include <cmath>
#include <iostream>
#include <assert.h>
#include "mydxwnd.h"

using namespace std;

#define MY_PI			3.14159265
#define MARGIN_OF_ERROR	0.001f
#define RAD2DEG(x)		((x) * (180.0f / MY_PI))
#define DEG2RAD(x)		((x) * (MY_PI / 180.0f))

struct MyPair2F
{
	union
	{
		struct { float x, y; };
		float p[2];
	};
};

struct MyPair3F
{
	union
	{
		struct { float x, y, z; };
		float p[3];
	};
};

struct MyVector2F : MyPair2F
{
	friend MyVector2F operator*(float scalar, const MyVector2F& opd);

public:
	MyVector2F();
	MyVector2F(float x, float y);
	MyVector2F(const MyVector2F& v);

public:
	MyVector2F	operator+(const MyVector2F& opd)	const;
	MyVector2F	operator+=(const MyVector2F& opd);
	MyVector2F	operator-(const MyVector2F& opd)	const;
	MyVector2F	operator-=(const MyVector2F& opd);
	MyVector2F	operator*(float scalar)				const;

	MyVector2F	operator-();

	bool		operator==(const MyVector2F& opd)	const;
	bool		operator!=(const MyVector2F& opd)	const;

public:
	void		set(float x, float y);
	float		length()							const;
	float		lengthSquare()						const;
	MyVector2F	getIdentity()						const;
	void		normalization();

	float		getDegAngle(const MyVector2F& opd)	const;
	float		getRadAngle(const MyVector2F& opd)	const;
public:
	static float getDistance2f(const MyVector2F& p1,
		const MyVector2F& p2);
	static float getDistanceSquare2f(const MyVector2F& p1,
		const MyVector2F& p2);
};

struct MyVector3F : MyPair3F
{
	friend MyVector3F operator*(float scalar, const MyVector3F& opd);

public:
	MyVector3F();
	MyVector3F(float x, float y, float z);
	MyVector3F(const MyVector3F& v);

public:
	MyVector3F	operator+(const MyVector3F& opd)	const;
	MyVector3F	operator+=(const MyVector3F& opd);
	MyVector3F	operator-(const MyVector3F& opd)	const;
	MyVector3F	operator-=(const MyVector3F& opd);
	MyVector3F	operator*(float scalar);

	MyVector3F	operator-();

	bool		operator==(const MyVector3F& opd)	const;
	bool		operator!=(const MyVector3F& opd)	const;

public:
	void		set(float x, float y, float z);
	float		length()							const;
	float		lengthSquare()						const;
	MyVector3F	getIdentity()						const;
	void		normalization();

	float		getDegAngle(const MyVector3F& opd)	const;
	float		getRadAngle(const MyVector3F& opd)	const;
public:
	static float getDistance(const MyVector3F& p1,
		const MyVector3F& p2);
	static float getDistanceSquare(const MyVector3F& p1,
		const MyVector3F& p2);
};


//testcase
/* 
void test_vector()
{
	MyVector2F A1(1, 1), B1(1, 0);

	MyVector2F C1 = A1 + B1;
	MyVector2F D1 = A1 - B1;
	MyVector2F E1(A1);
	E1 = 5.0f * E1;

	MyVector2F F1 = A1;
	MyVector2F G1 = B1;
	F1 += A1;
	G1 -= A1;

	MyVector2F H1 = -A1;

	bool isEqual = (A1 == A1);
	bool isNotEqual = (A1 != A1);

	B1.set(0, 1);

	cout << A1.lengthSquare() << " | " << A1.length() << "\n";

	MyVector2F I1 = A1.getIdentity();
	F1.normalization();
	cout << F1.length() << '\n';

	cout << "Radian : " << A1.getRadAngle(B1) << " | Degree : " << A1.getDegAngle(B1) << '\n';

	MyVector3F A2(1, 1, 1), B2(1, 0, 0);

	MyVector3F C2 = A2 + B2;
	MyVector3F D2 = A2 - B2;
	MyVector3F E2(A2);
	E2 = 5.0f * E2;

	MyVector3F F2 = A2;
	MyVector3F G2 = B2;
	F2 += A2;
	G2 -= A2;

	MyVector3F H2 = -A2;

	bool isEqual = (A2 == A2);
	bool isNotEqual = (A2 != A2);

	B2.set(0, 1, 1);

	cout << A2.lengthSquare() << " | " << A2.length() << "\n";

	MyVector3F I = A2.getIdentity();
	F2.normalization();
	cout << F2.length() << '\n';

	cout << "Radian : " << A2.getRadAngle(B2) << " | Degree : " << A2.getDegAngle(B2) << '\n';
}
*/