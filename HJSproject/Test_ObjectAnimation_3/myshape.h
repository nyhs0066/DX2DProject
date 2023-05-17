#pragma once
#include "myunih.h"

struct MyRect
{
	MyVector2F pos;
	MyVector2F fWH;

	bool operator==(const MyRect& opd);
	bool operator!=(const MyRect& opd);
};

