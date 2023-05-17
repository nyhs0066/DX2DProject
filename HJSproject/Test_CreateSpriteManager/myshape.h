#pragma once
#include "myunih.h"

struct MyRect
{
	union
	{
		FLOAT v[4];
		struct
		{
			MyVector2F pos;
			MyVector2F fWH;
		};
		MyVector4F rt;
	};

	MyRect();
	MyRect(FLOAT x, FLOAT y, FLOAT w, FLOAT h);
	MyRect(MyVector2F pos, MyVector2F fWH);
	MyRect(MyVector4F rt);
	MyRect(const MyRect& rt);

	bool operator==(const MyRect& opd);
	bool operator!=(const MyRect& opd);
};

