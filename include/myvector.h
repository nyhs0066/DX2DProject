#pragma once
#include "myunih.h"

#define MY_PI 3.1415926f
#define MY_TAU 6.2831853f

#define MY_RAD2DEG(x) (x)*(180.0f/MY_PI)
#define MY_DEG2RAD(x) (x)*(MY_PI/180.0f)

#define MY_MARGIN_OF_ERROR 0.0001f

struct MyFloat2F
{
	union
	{
		struct { FLOAT x, y; };
		FLOAT v[2];
	};
};

struct MyFloat3F
{
	union
	{
		struct { FLOAT x, y, z; };
		FLOAT v[3];
	};
};

struct MyFloat4F
{
	union
	{
		struct { FLOAT x, y, z, w; };
		FLOAT v[4];
	};
};

struct MyVector2F : MyFloat2F
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
	void		setZeroVector();
public:
	static float getDistance(const MyVector2F& p1,
		const MyVector2F& p2);
	static float getDistanceSquare(const MyVector2F& p1,
		const MyVector2F& p2);
};

struct MyVector3F : MyFloat3F
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
	void		setZeroVector();
public:
	static float getDistance(const MyVector3F& p1,
		const MyVector3F& p2);
	static float getDistanceSquare(const MyVector3F& p1,
		const MyVector3F& p2);
};

struct MyVector4F : MyFloat4F
{
	friend MyVector4F operator*(float scalar, const MyVector4F& opd);

public:
	MyVector4F();
	MyVector4F(float x, float y, float z, float w);
	MyVector4F(const MyVector4F& v);

public:
	MyVector4F	operator+(const MyVector4F& opd)	const;
	MyVector4F	operator+=(const MyVector4F& opd);
	MyVector4F	operator-(const MyVector4F& opd)	const;
	MyVector4F	operator-=(const MyVector4F& opd);
	MyVector4F	operator*(float scalar);

	MyVector4F	operator-();

	bool		operator==(const MyVector4F& opd)	const;
	bool		operator!=(const MyVector4F& opd)	const;

public:
	void		set(float x, float y, float z, float w);
	float		length()							const;
	float		lengthSquare()						const;
	MyVector4F	getIdentity()						const;
	void		normalization();

	float		getDegAngle(const MyVector4F& opd)	const;
	float		getRadAngle(const MyVector4F& opd)	const;
	void		setZeroVector();
public:
	static float getDistance(const MyVector4F& p1,
		const MyVector4F& p2);
	static float getDistanceSquare(const MyVector4F& p1,
		const MyVector4F& p2);
};

struct NormalVertex
{
	MyVector3F p;
	MyVector4F n;
	MyVector4F c;
	MyVector2F t;
};