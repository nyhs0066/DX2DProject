#include "myshape.h"

MyRect::MyRect()
{
	for (int i = 0; i < 4; i++) { v[i] = 0.0f; }
}

MyRect::MyRect(FLOAT x, FLOAT y, FLOAT w, FLOAT h)
{
	v[0] = x;
	v[1] = y;
	v[2] = w;
	v[3] = h;
}

MyRect::MyRect(MyVector2F pos, MyVector2F fWH)
{
	this->pos = pos;
	this->fWH = fWH;
}

MyRect::MyRect(MyVector4F rt)
{
	this->rt = rt;
}

MyRect::MyRect(const MyRect& rt)
{
	*this = rt;
}

bool MyRect::operator==(const MyRect& opd)
{
	return (this->pos == opd.pos) && (this->fWH == opd.fWH);
}

bool MyRect::operator!=(const MyRect& opd)
{
	return !(*this == opd);
}