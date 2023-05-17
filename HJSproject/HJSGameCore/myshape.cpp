#include "myshape.h"

MyShape::~MyShape() {}

MyCircle::MyCircle() : MyCircle(0.0f, 0.0f, 0.0f) {}

MyCircle::MyCircle(FLOAT cx, FLOAT cy, FLOAT r) { set(cx, cy, r); }

MyCircle::MyCircle(MyVector2F cPos, FLOAT r) { set(cPos, r); }

MyCircle::MyCircle(MyVector2F cPos, MyVector2F pt) { set(cPos, pt); }

MyCircle::MyCircle(const MyCircle& C) { set(C); }

void MyCircle::set(FLOAT cx, FLOAT cy, FLOAT r)
{
	cPos.x = cx;
	cPos.y = cy;
	radius = r;
}

void MyCircle::set(MyVector2F cPos, FLOAT r)
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
	radius = MyVector2F::getDistance(cPos, pt);
}

bool MyCircle::operator==(const MyCircle& opd)
{
	return (cPos == opd.cPos && (fabs(radius - opd.radius) < MY_MARGIN_OF_ERROR));
}

bool MyCircle::operator!=(const MyCircle& opd)
{
	return !(*this == opd);
}

MyRect::MyRect() : MyRect(0.0f, 0.0f, 0.0f, 0.0f) {}

MyRect::MyRect(FLOAT x, FLOAT y, FLOAT w, FLOAT h) { set(x, y, w, h); }

MyRect::MyRect(MyVector2F pos, MyVector2F fWH) { set(pos, fWH); }

MyRect::MyRect(MyVector4F rt)
{
	this->rt = rt;
}

MyRect::MyRect(const MyRect& rt) { set(rt); }

void MyRect::set(FLOAT x, FLOAT y, FLOAT w, FLOAT h)
{
	v[0] = x;
	v[1] = y;
	v[2] = w;
	v[3] = h;
}

void MyRect::set(MyVector2F pos, MyVector2F fWH)
{
	this->pos = pos;
	this->fWH = fWH;
}

void MyRect::set(MyVector4F rt) { this->rt = rt; }

void MyRect::set(const MyRect& R)
{
	pos = R.pos;
	fWH = R.fWH;
}

MyVector2F MyRect::getCpos()
{
	return MyVector2F(pos.x + fWH.x * 0.5f, pos.y + fWH.y * 0.5f);
}

MyVector2F MyRect::getRBPos()
{
	return MyVector2F(pos.x + fWH.x, pos.y + fWH.y);
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

MySphere::MySphere(FLOAT cx, FLOAT cy, FLOAT cz, FLOAT r) { set(cx, cy, cz, r); }

MySphere::MySphere(MyVector3F cPos, FLOAT r) { set(cPos, r); }

MySphere::MySphere(const MySphere& C) { set(C); }

MySphere::MySphere(MyVector3F cPos, MyVector3F pt) { set(cPos, pt); }

void MySphere::set(FLOAT cx, FLOAT cy, FLOAT cz, FLOAT r)
{
	cPos.x = cx;
	cPos.y = cy;
	cPos.z = cz;
	radius = r;
}

void MySphere::set(MyVector3F cPos, FLOAT r)
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
	return (cPos == opd.cPos && (fabs(radius - opd.radius) < MY_MARGIN_OF_ERROR));
}

bool MySphere::operator!=(const MySphere& opd)
{
	return !(*this == opd);
}

MyCube::MyCube() : MyCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) {}

MyCube::MyCube(FLOAT x, FLOAT y, FLOAT z, FLOAT width, FLOAT length, FLOAT height)
{
	set(x, y, z, width, length, height);
}

MyCube::MyCube(MyVector3F pos, MyVector3F fWLH) { set(pos, fWLH); }

MyCube::MyCube(const MyCube& R) { set(R); }

void MyCube::set(FLOAT x, FLOAT y, FLOAT z, FLOAT width, FLOAT length, FLOAT height)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = width;
	v[4] = length;
	v[5] = height;
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

MyVector3F MyCube::getCpos()
{
	return MyVector3F(pos.x + fWLH.x * 0.5f, pos.y + fWLH.y * 0.5f, pos.z + fWLH.z * 0.5f);
}

MyVector3F MyCube::getRBPos()
{
	return MyVector3F(pos.x + fWLH.x, pos.y + fWLH.y, pos.z + fWLH.z);
}

bool MyCube::operator==(const MyCube& opd)
{
	return (pos == opd.pos && fWLH == opd.fWLH);
}

bool MyCube::operator!=(const MyCube& opd)
{
	return !(*this == opd);
}

MyExRect::MyExRect() : MyRect(0.0f, 0.0f, 0.0f, 0.0f)
{
}

MyExRect::MyExRect(FLOAT x, FLOAT y, FLOAT w, FLOAT h)
{
	set(x, y, w, h);
}

MyExRect::MyExRect(MyVector2F pos, MyVector2F fWH)
{
	set(pos, fWH);
}

MyExRect::MyExRect(MyVector4F rt)
{
	set(rt);
}

MyExRect::MyExRect(const MyExRect& rt)
{
	*this = rt;
}

void MyExRect::set(FLOAT x, FLOAT y, FLOAT w, FLOAT h)
{
	MyRect::set(x, y, w, h);

	LTpos = { x, y };
	RTpos = { x + w, y };
	LBpos = { x, y + h };
	RBpos = { x + w, y + h };
}

void MyExRect::set(MyVector2F pos, MyVector2F fWH)
{
	MyRect::set(pos, fWH);

	LTpos = pos;
	RTpos = { pos.x + fWH.x, pos.y };
	LBpos = { pos.x, pos.y + fWH.y };
	RBpos = { pos.x + fWH.x, pos.y + fWH.y };
}

void MyExRect::set(MyVector4F rt)
{
	MyRect::set(rt);

	LTpos = { rt.v[0], rt.v[1] };
	RTpos = { rt.v[0] + rt.v[2], rt.v[1] };
	LBpos = { rt.v[0], rt.v[1] + rt.v[3] };
	RBpos = { rt.v[0] + rt.v[2], rt.v[1] + rt.v[3] };
}

void MyExRect::set(const MyRect& rt)
{
	MyRect::set(rt);

	LTpos = rt.pos;
	RTpos = { rt.pos.x + rt.fWH.x , rt.pos.y };
	LBpos = { rt.pos.x , rt.pos.y + rt.fWH.y };;
	RBpos = { rt.pos.x + rt.fWH.x , rt.pos.y + rt.fWH.y };
}