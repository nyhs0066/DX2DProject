#include "mybaseobject.h"

MyBaseObject::MyBaseObject() 
{
	pVertexBuf = nullptr;
	pObjTexture = nullptr;
	pObjShader = nullptr;
};
MyBaseObject::~MyBaseObject() 
{
	release();
};

bool MyBaseObject::create(wstring wszShaderFileName, wstring wszTextureFileName)
{
	HRESULT hr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(MyVertex) * vertices.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = &vertices.at(0);

	hr = I_DEVICE->CreateBuffer(&bd, &sd, &pVertexBuf);
	if (FAILED(hr)) { return false; }

	pObjTexture = LOAD_TEXTURE(wszTextureFileName);
	if (!pObjTexture) { return false; }

	pObjShader = LOAD_SHADER(wszShaderFileName);
	if (!pObjShader) { return false; }

	return true;
}

bool MyBaseObject::release()
{
	vertices.clear();
	if (pVertexBuf) { pVertexBuf->Release(); pVertexBuf = nullptr; };

	pObjTexture = nullptr;
	pObjShader = nullptr;

	return true;
}

bool MyBaseObject::preRender()
{
	UINT stride = sizeof(MyVertex);
	UINT offset = 0;
	I_DCONTEXT->IASetVertexBuffers(0, 1, &pVertexBuf, &stride, &offset);
	I_DCONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pObjShader->render();

	ID3D11ShaderResourceView* pSRV = pObjTexture->getSRView();
	I_DCONTEXT->PSSetShaderResources(0, 1, &pSRV);

	return true;
}

bool MyBaseObject::postRender()
{
	I_DCONTEXT->Draw(vertices.size(), 0);
	return true;
}

MyRectObject::MyRectObject()
{
	MyVector3F iPos;
	MyVector4F iColor(1.0f, 1.0f, 1.0f, 1.0f);
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(30.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 30.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(0.0f, 30.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(30.0f, 0.0f) });
	vertices.push_back({ iPos, iColor, MyVector2F(30.0f, 30.0f) });
}

MyRectObject::~MyRectObject()
{
	release();
}

bool MyRectObject::setRect(MyVector2F pos, MyVector2F fWH)
{
	this->pos = pos;
	this->fWH = fWH;

	setPosition(pos);
	return true;
}

bool MyRectObject::setPosition(MyVector2F nPos)
{
	this->pos = pos;

	FLOAT LTX = ((pos.x / MyWindow::cWidth) * 2 - 1.0f);
	FLOAT LTY = -((pos.y / MyWindow::cHeight) * 2 - 1.0f);
	FLOAT RBX = LTX + (fWH.v[0] / MyWindow::cWidth) * 2;
	FLOAT RBY = LTY -((fWH.v[1] / MyWindow::cHeight) * 2);

	vertices[0].p = { LTX, LTY, 0.0f };
	vertices[1].p = { RBX, LTY, 0.0f };
	vertices[2].p = { LTX, RBY, 0.0f };
	vertices[3].p = { LTX, RBY, 0.0f };
	vertices[4].p = { RBX, LTY, 0.0f };
	vertices[5].p = { RBX, RBY, 0.0f };

	return true;
}

bool MyRectObject::init()
{
	return true;
}

bool MyRectObject::frame()
{
	I_DCONTEXT->UpdateSubresource(pVertexBuf, 0, nullptr,
		&vertices.at(0), 0, 0);
	return true;
}

bool MyRectObject::render()
{
	preRender();

	//TO DO

	postRender();
	return true;
}

bool MyRectObject::release()
{
	return true;
}
