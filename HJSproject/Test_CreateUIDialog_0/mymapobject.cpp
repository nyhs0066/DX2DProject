#include "mymapobject.h"

MyMapObject2D::MyMapObject2D()
{

}

MyMapObject2D::~MyMapObject2D()
{

}

MyTile2D::MyTile2D()
{

}

MyTile2D::~MyTile2D()
{
	
}

MyTilePlatform2D::MyTilePlatform2D()
{
}

MyTilePlatform2D::~MyTilePlatform2D()
{
}

bool MyTilePlatform2D::frame()
{
	for (vector<MyMapObject2D*>::iterator::value_type it : m_mapObjList)
	{
		it->frame();
	}

	return true;
}

bool MyTilePlatform2D::postFrame(const MyRect& camRt)
{
	for (vector<MyMapObject2D*>::iterator::value_type it : m_mapObjList)
	{
		it->postFrame(camRt);
	}

	return true;
}

bool MyTilePlatform2D::render()
{
	for (vector<MyMapObject2D*>::iterator::value_type it : m_mapObjList)
	{
		it->render();
	}

	return true;
}

bool MyTilePlatform2D::release()
{
	for (vector<MyMapObject2D*>::iterator::value_type it : m_mapObjList)
	{
		it->release();
		delete it;
		it = nullptr;
	}

	return true;
}
