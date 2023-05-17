#include "mymapobject.h"

MyMapObject::MyMapObject()
{

}

MyMapObject::~MyMapObject()
{
	release();
}

MyTile::MyTile()
{

}

MyTile::~MyTile()
{
	
}

MyTilePlatform::MyTilePlatform()
{
	m_pChildren.clear();
}

MyTilePlatform::~MyTilePlatform()
{
}

bool MyTilePlatform::frame()
{
	MyExRect temp;

	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		temp = it->m_SPRect;
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->frame();
	}

	return true;
}

bool MyTilePlatform::postFrame(const MyExRect& camRt, FLOAT radian)
{
	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		it->postFrame(camRt, radian);
	}

	return true;
}

bool MyTilePlatform::render()
{
	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		it->render();
	}

	return true;
}

bool MyTilePlatform::release()
{
	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		it->release();
		delete it;
		it = nullptr;
	}

	return true;
}

bool MyTilePlatform::addChild(MyMapObject* pMObj)
{
	m_pChildren.push_back(pMObj);

	return true;
}

bool MyMapObject::addChild(MyMapObject* pMObj)
{
	return true;
}
