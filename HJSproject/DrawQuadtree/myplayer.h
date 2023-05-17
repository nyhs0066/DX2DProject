#pragma once
#include "myobject.h"

class Player2F : public MyObject2F
{
public:
	Player2F();
	Player2F(float x, float y, float width, float height);
	Player2F(MyVector2F pos, MyVector2F fWH);
	Player2F(MyRect rect);

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;
};

class Player3F : public MyObject3F
{
public:
	Player3F();
	Player3F(float x, float y, float z, float width, float length, float height);
	Player3F(MyVector3F pos, MyVector3F fWLH);
	Player3F(MyCube cube);

	void frame(const MyShape* boundary, float deltaT, float gameT) override;
	void draw() override;
};