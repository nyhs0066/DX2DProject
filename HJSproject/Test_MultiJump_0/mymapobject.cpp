#include "mymapobject.h"

MyMapObject::MyMapObject()
{

}

MyMapObject::~MyMapObject()
{

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
	MyRect temp;

	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		temp = it->getPosRect();
		temp.pos += m_posOffset;
		it->setPosRect(temp);
		it->frame();
	}

	return true;
}

bool MyTilePlatform::postFrame(const MyRect& camRt)
{
	for (vector<MyMapObject*>::iterator::value_type it : m_pChildren)
	{
		it->postFrame(camRt);
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
