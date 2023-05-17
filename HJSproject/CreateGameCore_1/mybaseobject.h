#pragma once
#include "myrendermanager.h"
#include "myvector.h"

struct MyVertex
{
	MyVector3F p;
	MyVector4F c;
	MyVector2F t;
};

class MyBaseObject
{
protected:
	static MyVector4F boundary;

	vector<MyVertex> vertices;
	ID3D11Buffer* pVertexBuf;

public:
	MyBaseObject();
	virtual ~MyBaseObject();

	bool create();
	//bool loadTexture();

	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
};

class MySquare : public MyBaseObject
{
protected:
	MyVector2F pos;
	MyVector2F fWH;

public:
	MySquare();
	~MySquare();

	bool setRect(MyVector2F pos, MyVector2F fWH);
	bool setPosition(MyVector2F nPos);

	bool init();
	bool frame();
	bool render();
	bool release();
};