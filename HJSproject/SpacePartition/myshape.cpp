#include "myshape.h"

MyShape::~MyShape() {}

MyCircle::MyCircle() : MyCircle(0.0f, 0.0f, 0.0f) {}

MyCircle::MyCircle(float cx, float cy, float r) { set(cx, cy, r); }

MyCircle::MyCircle(MyVector2F cPos, float r) { set(cPos, r); }

MyCircle::MyCircle(MyVector2F cPos, MyVector2F pt) { set(cPos, pt); }

MyCircle::MyCircle(const MyCircle& C) { set(C); }

void MyCircle::set(float cx, float cy, float r)
{
	cPos.x = cx;
	cPos.y = cy;
	radius = r;
}

void MyCircle::set(MyVector2F cPos, float r)
{
	this->cPos = cPos;
	this->radius = r;
}

void MyCircle::set(const MyCircle& C)
{
	cPos = C.cPos;
	radius = C.radius;
}

void MyCircle::set(MyVector2F cPos, MyVector2F pt)
{
	this->cPos = cPos;
	radius = MyVector2F::getDistance2f(cPos, pt);
}

bool MyCircle::operator==(const MyCircle& opd)
{
	return (cPos == opd.cPos && (fabs(radius - opd.radius) < MARGIN_OF_ERROR));
}

bool MyCircle::operator!=(const MyCircle& opd)
{
	return !(*this == opd);
}

MyRect::MyRect() : MyRect(0.0f, 0.0f, 0.0f, 0.0f) {}

MyRect::MyRect(float x, float y, float width, float height)
{
	set(x, y, width, height);
}

MyRect::MyRect(MyVector2F pos, MyVector2F fWH) { set(pos, fWH); }

MyRect::MyRect(const MyRect& R) { set(R); }

void MyRect::set(float x, float y, float width, float height)
{
	pos.x = x;
	pos.y = y;
	fWH.p[0] = width;
	fWH.p[1] = height;
}

void MyRect::set(MyVector2F pos, MyVector2F fWH)
{
	this->pos = pos;
	this->fWH = fWH;
}

void MyRect::set(const MyRect& R)
{
	pos = R.pos;
	fWH = R.fWH;
}

MyVector2F MyRect::getCTPoint() const
{
	float x = pos.x + fWH.p[0] / 2.0f;
	float y = pos.y + fWH.p[1] / 2.0f;
	return MyVector2F(x, y);
}

MyVector2F MyRect::getRBPoint() const
{
	float x = pos.x + fWH.p[0];
	float y = pos.y + fWH.p[1];
	return MyVector2F(x, y);
}

bool MyRect::operator==(const MyRect& opd)
{
	return (pos == opd.pos && fWH == opd.fWH);
}

bool MyRect::operator!=(const MyRect& opd)
{
	return !(*this == opd);
}

MySphere::MySphere() : MySphere(0.0f, 0.0f, 0.0f, 0.0f) {}

MySphere::MySphere(float cx, float cy, float cz, float r) { set(cx, cy, cz, r); }

MySphere::MySphere(MyVector3F cPos, float r) { set(cPos, r); }

MySphere::MySphere(const MySphere& C) { set(C); }

MySphere::MySphere(MyVector3F cPos, MyVector3F pt) { set(cPos, pt); }

void MySphere::set(float cx, float cy, float cz, float r)
{
	cPos.x = cx;
	cPos.y = cy;
	cPos.z = cz;
	radius = r;
}

void MySphere::set(MyVector3F cPos, float r)
{
	this->cPos = cPos;
	radius = r;
}

void MySphere::set(const MySphere& C)
{
	cPos = C.cPos;
	radius = C.radius;
}

void MySphere::set(MyVector3F cPos, MyVector3F pt)
{
	this->cPos = cPos;
	radius = MyVector3F::getDistance(cPos, pt);
}

bool MySphere::operator==(const MySphere& opd)
{
	return (cPos == opd.cPos && (fabs(radius - opd.radius) < MARGIN_OF_ERROR));
}

bool MySphere::operator!=(const MySphere& opd)
{
	return !(*this == opd);
}

MyCube::MyCube() : MyCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {}

MyCube::MyCube(float x, float y, float z, float width, float length, float height)
{
	set(x, y, z, width, length, height);
}

MyCube::MyCube(MyVector3F pos, MyVector3F fWLH) { set(pos, fWLH); }

MyCube::MyCube(const MyCube& R) { set(R); }

void MyCube::set(float x, float y, float z, float width, float length, float height)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	fWLH.p[0] = width;
	fWLH.p[1] = length;
	fWLH.p[2] = height;
}

void MyCube::set(MyVector3F pos, MyVector3F fWLH)
{
	this->pos = pos;
	this->fWLH = fWLH;
}

void MyCube::set(const MyCube& R)
{
	pos = R.pos;
	fWLH = R.fWLH;
}

MyVector3F MyCube::getCTPoint() const
{
	float x = pos.x + fWLH.p[0] / 2.0f;
	float y = pos.y + fWLH.p[1] / 2.0f;
	float z = pos.z + fWLH.p[2] / 2.0f;
	return MyVector3F(x, y, z);
}

MyVector3F MyCube::getFRBPoint() const
{
	float x = pos.x + fWLH.p[0];
	float y = pos.y + fWLH.p[1];
	float z = pos.z + fWLH.p[2];
	return MyVector3F(x, y, z);
}

bool MyCube::operator==(const MyCube& opd)
{
	return (pos == opd.pos && fWLH == opd.fWLH);
}

bool MyCube::operator!=(const MyCube& opd)
{
	return !(*this == opd);
}

