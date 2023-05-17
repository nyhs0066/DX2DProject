#include "myshapes.h"

bool MyCube::operator==(const MyCube& opd)
{
	return (this->pos == opd.pos) && (this->fWLH == opd.fWLH);
}

bool MyCube::operator!=(const MyCube& opd)
{
	return !(*this == opd);
}