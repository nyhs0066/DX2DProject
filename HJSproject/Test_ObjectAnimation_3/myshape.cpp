#include "myshape.h"

bool MyRect::operator==(const MyRect& opd)
{
	return (this->pos == opd.pos) && (this->fWH == opd.fWH);
}

bool MyRect::operator!=(const MyRect& opd)
{
	return !(*this == opd);
}