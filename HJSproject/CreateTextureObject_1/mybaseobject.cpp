#include "mybaseobject.h"

MyVector4F MyBaseObject::boundary = { 0, 0, 128, 128 };

MyBaseObject::MyBaseObject() 
{
	pVertexBuf = nullptr;
};
MyBaseObject::~MyBaseObject() 
{
	release();
};

bool MyBaseObject::create()
{
	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(MyVertex) * vertices.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = &vertices.at(0);

	hr = MYDEVICE->CreateBuffer(&bd, &sd, &pVertexBuf);
	if (FAILED(hr)) { return false; }

	return true;
}

bool MyBaseObject::init()
{
	return true;
}

bool MyBaseObject::frame()
{
	return true;
}

bool MyBaseObject::render()
{
	return true;
}

bool MyBaseObject::release()
{
	vertices.clear();
	if (pVertexBuf) { pVertexBuf->Release(); pVertexBuf = nullptr; };

	return true;
}

MySquare::MySquare()
{
	MyVector3F iPos;
	MyVector4F iColor(1.0f, 1.0f, 1.0f, 1.0f);
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(1.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 1.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 1.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(1.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(1.0f, 1.0f) });
}

MySquare::~MySquare()
{
	release();
}

bool MySquare::setRect(MyVector2F pos, MyVector2F fWH)
{
	this->pos = pos;
	this->fWH = fWH;

	setPosition(pos);
	return true;
}

bool MySquare::setPosition(MyVector2F nPos)
{
	this->pos = pos;

	FLOAT LTX = ((pos.x / boundary.p[2])*2 - 1.0f);
	FLOAT LTY = -((pos.y / boundary.p[3]) * 2 - 1.0f);
	FLOAT RBX = (((pos.x + fWH.p[0]) / boundary.p[2]) * 2 - 1.0f);
	FLOAT RBY = -(((pos.y + fWH.p[1]) / boundary.p[3]) * 2 - 1.0f);

	vertices[0].p = { LTX, LTY, 0.0f };
	vertices[1].p = { RBX, LTY, 0.0f };
	vertices[2].p = { LTX, RBY, 0.0f };
	vertices[3].p = { LTX, RBY, 0.0f };
	vertices[4].p = { RBX, LTY, 0.0f };
	vertices[5].p = { RBX, RBY, 0.0f };

	return true;
}

bool MySquare::init()
{
	return false;
}

bool MySquare::frame()
{
	MYDCONTEXT->UpdateSubresource(pVertexBuf, 0, nullptr,
		&vertices.at(0), 0, 0);
	return false;
}

bool MySquare::render()
{
	UINT stride = sizeof(MyVector4F);
	UINT offset = 0;
	MYDCONTEXT->IASetVertexBuffers(0, 1, &pVertexBuf, &stride, &offset);
	//SETVLAYOUT
	MYDCONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return false;
}

bool MySquare::release()
{
	return false;
}
