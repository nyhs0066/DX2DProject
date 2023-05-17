#pragma once
#include "myobject2d.h"

//ī�޶�� ��ī��Ʈ ��ǥ�踦 ����Ѵ�.
//ī�޶��� ��ġ�� ī�޶� ���� ������ ���߾ӿ� �ִٴ� ���� ����
class MyCamera
{
protected:
	int			iPrevWidth;
	int			iPrevHeight;

	MyRect m_Camera;
	MyRect m_bRect;
	MyObject2D* m_pFollowing;

public:
	MyCamera();
	~MyCamera();

	bool			init();
	bool			frame();
	bool			render();
	bool			release();

	//������ �Ǿ������� �� �����Ӹ��� �ڵ����� ī�޶� ��ġ�� ���ŵȴ�.
	void			setFollowTarget(MyObject2D* pObj);
	void			setBoundaryRect(const MyRect& bRect);

	void			setCamPos(const MyVector2F& pos);
	void			setCamArea(const MyVector2F& fWH);
	void			setCamRect(const MyRect& rt);

	MyVector2F		getCamPos() const;
	MyVector2F		getCamArea() const;
	MyRect			getCamRect() const;

	bool isResized();

	void zoom(int magnification);
};