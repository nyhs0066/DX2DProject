#include "myvector.h"

MyVector2F::MyVector2F() : MyVector2F(0.0f, 0.0f) {}

MyVector2F::MyVector2F(float x, float y) { set(x, y); }

MyVector2F::MyVector2F(const MyVector2F& v) { set(v.x, v.y); }

MyVector2F MyVector2F::operator+(const MyVector2F& opd)	const
{
	return MyVector2F(x + opd.x, y + opd.y);
}

MyVector2F MyVector2F::operator+=(const MyVector2F& opd)
{
	x += opd.x;
	y += opd.y;
	return *this;
}

MyVector2F MyVector2F::operator-(const MyVector2F& opd)	const
{
	return MyVector2F(x - opd.x, y - opd.y);
}

MyVector2F MyVector2F::operator-=(const MyVector2F& opd)
{
	x -= opd.x;
	y -= opd.y;
	return *this;
}

MyVector2F MyVector2F::operator*(float scalar)	const
{
	return MyVector2F(x * scalar, y * scalar);
}

MyVector2F MyVector2F::operator-()
{
	return MyVector2F(-x, -y);
}

bool MyVector2F::operator==(const MyVector2F& opd)	const
{
	if (fabs(x - opd.x) < MY_MARGIN_OF_ERROR)
	{
		if (fabs(y - opd.y) < MY_MARGIN_OF_ERROR) { return true; }
	}
	return false;
}

bool MyVector2F::operator!=(const MyVector2F& opd) const { return !(*this == opd); }

void MyVector2F::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float MyVector2F::length() const { return sqrtf(lengthSquare()); }

float MyVector2F::lengthSquare() const { return x * x + y * y; }

MyVector2F MyVector2F::getIdentity() const
{
	float len = 1.0f / length();
	return MyVector2F(x * len, y * len);
}

void MyVector2F::normalization()
{
	float len = 1.0f / length();
	x *= len;
	y *= len;
}

float MyVector2F::getDegAngle(const MyVector2F& opd) const
{
	return MY_RAD2DEG(getRadAngle(opd));
}

float MyVector2F::getRadAngle(const MyVector2F& opd) const
{
	float dotProduct = x * opd.x + y * opd.y;
	float inverseLen = 1.0f / (length() * opd.length());

	return acosf(dotProduct * inverseLen);
}

void MyVector2F::setZeroVector()
{
	x = y = 0.0f;
}

MyVector2F operator*(float scalar, const MyVector2F& opd)
{
	return MyVector2F(scalar * opd.x, scalar * opd.y);
}

float MyVector2F::getDistance(const MyVector2F& p1, const MyVector2F& p2)
{
	return sqrtf(getDistanceSquare(p1, p2));
}

float MyVector2F::getDistanceSquare(const MyVector2F& p1, const MyVector2F& p2)
{
	float ret = 0;
	for (int i = 0; i < 2; i++) { ret += powf(p1.v[i] - p2.v[i], 2); }

	return ret;
}

MyVector3F::MyVector3F() : MyVector3F(0.0f, 0.0f, 0.0f) {}

MyVector3F::MyVector3F(float x, float y, float z) { set(x, y, z); }

MyVector3F::MyVector3F(const MyVector3F& v) { set(v.x, v.y, v.z); }

MyVector3F MyVector3F::operator+(const MyVector3F& opd)	const
{
	return MyVector3F(x + opd.x, y + opd.y, z + opd.z);
}

MyVector3F MyVector3F::operator+=(const MyVector3F& opd)
{
	x += opd.x;
	y += opd.y;
	z += opd.z;
	return *this;
}

MyVector3F MyVector3F::operator-(const MyVector3F& opd)	const
{
	return MyVector3F(x - opd.x, y - opd.y, z - opd.z);
}

MyVector3F MyVector3F::operator-=(const MyVector3F& opd)
{
	x -= opd.x;
	y -= opd.y;
	z -= opd.z;
	return *this;
}

MyVector3F MyVector3F::operator*(float scalar)
{
	return MyVector3F(x * scalar, y * scalar, z * scalar);
}

MyVector3F MyVector3F::operator-()
{
	return MyVector3F(-x, -y, -z);
}

bool MyVector3F::operator==(const MyVector3F& opd)	const
{
	if (fabs(x - opd.x) < MY_MARGIN_OF_ERROR)
	{
		if (fabs(y - opd.y) < MY_MARGIN_OF_ERROR)
		{
			if (fabs(z - opd.z) < MY_MARGIN_OF_ERROR) { return true; }
		}
	}
	return false;
}

bool MyVector3F::operator!=(const MyVector3F& opd) const { return !(*this == opd); }

void MyVector3F::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float MyVector3F::length() const { return sqrtf(lengthSquare()); }

float MyVector3F::lengthSquare() const { return x * x + y * y + z * z; }

MyVector3F MyVector3F::getIdentity() const
{
	float len = 1.0f / length();
	return MyVector3F(x * len, y * len, z * len);
}

void MyVector3F::normalization()
{
	float len = 1.0f / length();
	x *= len;
	y *= len;
	z *= len;
}

float MyVector3F::getDegAngle(const MyVector3F& opd) const
{
	return MY_RAD2DEG(getRadAngle(opd));
}

float MyVector3F::getRadAngle(const MyVector3F& opd) const
{
	float dotProduct = x * opd.x + y * opd.y + z * opd.z;
	float inverseLen = 1.0f / (length() * opd.length());

	return acosf(dotProduct * inverseLen);
}

void MyVector3F::setZeroVector()
{
	x = y = z = 0.0f;
}

MyVector3F operator*(float scalar, const MyVector3F& opd)
{
	return MyVector3F(scalar * opd.x, scalar * opd.y, scalar * opd.z);
}

float MyVector3F::getDistance(const MyVector3F& p1, const MyVector3F& p2)
{
	return sqrtf(getDistanceSquare(p1, p2));
}

float MyVector3F::getDistanceSquare(const MyVector3F& p1, const MyVector3F& p2)
{
	float ret = 0;
	for (int i = 0; i < 3; i++) { ret += powf(p1.v[i] - p2.v[i], 2); }

	return ret;
}

MyVector4F::MyVector4F() : MyVector4F(0.0f, 0.0f, 0.0f, 0.0f) {}

MyVector4F::MyVector4F(float x, float y, float z, float w) { set(x, y, z,  w); }

MyVector4F::MyVector4F(const MyVector4F& v) { set(v.x, v.y, v.z, v.w); }

MyVector4F MyVector4F::operator+(const MyVector4F& opd)	const
{
	return MyVector4F(x + opd.x, y + opd.y, z + opd.z, w + opd.w);
}

MyVector4F MyVector4F::operator+=(const MyVector4F& opd)
{
	x += opd.x;
	y += opd.y;
	z += opd.z;
	w += opd.w;
	return *this;
}

MyVector4F MyVector4F::operator-(const MyVector4F& opd)	const
{
	return MyVector4F(x - opd.x, y - opd.y, z - opd.z, w - opd.w);
}

MyVector4F MyVector4F::operator-=(const MyVector4F& opd)
{
	x -= opd.x;
	y -= opd.y;
	z -= opd.z;
	w -= opd.w;
	return *this;
}

MyVector4F MyVector4F::operator*(float scalar)
{
	return MyVector4F(x * scalar, y * scalar, z * scalar, w * scalar);
}

MyVector4F MyVector4F::operator-()
{
	return MyVector4F(-x, -y, -z, -w);
}

bool MyVector4F::operator==(const MyVector4F& opd)	const
{
	if (fabs(x - opd.x) < MY_MARGIN_OF_ERROR)
	{
		if (fabs(y - opd.y) < MY_MARGIN_OF_ERROR)
		{
			if (fabs(z - opd.z) < MY_MARGIN_OF_ERROR)
			{
				if (fabs(z - opd.z) < MY_MARGIN_OF_ERROR) { return true; }
			}
		}
	}
	return false;
}

bool MyVector4F::operator!=(const MyVector4F& opd) const { return !(*this == opd); }

void MyVector4F::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float MyVector4F::length() const { return sqrtf(lengthSquare()); }

float MyVector4F::lengthSquare() const { return x * x + y * y + z * z + w * w; }

MyVector4F MyVector4F::getIdentity() const
{
	float len = 1.0f / length();
	return MyVector4F(x * len, y * len, z * len, w * len);
}

void MyVector4F::normalization()
{
	float len = 1.0f / length();
	x *= len;
	y *= len;
	z *= len;
	w *= len;
}

float MyVector4F::getDegAngle(const MyVector4F& opd) const
{
	return MY_RAD2DEG(getRadAngle(opd));
}

float MyVector4F::getRadAngle(const MyVector4F& opd) const
{
	float dotProduct = x * opd.x + y * opd.y + z * opd.z + w* opd.w;
	float inverseLen = 1.0f / (length() * opd.length());

	return acosf(dotProduct * inverseLen);
}

void MyVector4F::setZeroVector()
{
	x = y = z = w = 0.0f;
}

MyVector4F operator*(float scalar, const MyVector4F& opd)
{
	return MyVector4F(scalar * opd.x, scalar * opd.y, scalar * opd.z, scalar * opd.w);
}

float MyVector4F::getDistance(const MyVector4F& p1, const MyVector4F& p2)
{
	return sqrtf(getDistanceSquare(p1, p2));
}

float MyVector4F::getDistanceSquare(const MyVector4F& p1, const MyVector4F& p2)
{
	float ret = 0;
	for (int i = 0; i < 4; i++) { ret += powf(p1.v[i] - p2.v[i], 2); }

	return ret;
}