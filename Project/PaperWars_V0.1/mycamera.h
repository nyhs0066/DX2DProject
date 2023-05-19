#pragma once
#include "myobject2d.h"

//카메라는 데카르트 좌표계를 사용한다.
//카메라의 위치는 카메라가 보는 영역의 정중앙에 있다는 것을 유의
class MyCamera
{
protected:
	int			iPrevWidth;
	int			iPrevHeight;

	MyExRect m_Camera;
	MyExRect m_bRect;
	MyObject2D* m_pFollowing;

public:
	MyCamera();
	~MyCamera();

	bool			init();
	bool			frame();
	bool			render();
	bool			release();

	//설정이 되어있으면 매 프레임마다 자동으로 카메라 위치가 갱신된다.
	void			setFollowTarget(MyObject2D* pObj);
	void			setBoundaryRect(const MyExRect& bRect);

	void			setCamPos(const MyVector2F& pos);
	void			setCamArea(const MyVector2F& fWH);
	void			setCamRect(const MyExRect& rt);

	MyVector2F		getCamPos() const;
	MyVector2F		getCamArea() const;
	MyExRect			getCamRect() const;

	bool isResized();

	void zoom(int magnification);
};