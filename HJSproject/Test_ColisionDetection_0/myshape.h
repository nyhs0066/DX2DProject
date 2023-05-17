#pragma once
#include "myunih.h"

struct MyCube
{
	MyVector3F pos;
	MyVector3F fWLH;

	bool operator==(const MyCube& opd);
	bool operator!=(const MyCube& opd);
};

