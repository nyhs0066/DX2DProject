#pragma once
#include "mybaseobject.h"
#include "myshape.h"

class MyObject2D : public MyBaseObject
{
protected:
	MyTexture* m_pMaskTexture;

	MyVector2F m_vDirection;
	MyVector2F m_vForce;
	MyVector2F m_vAcceleration;
	MyVector2F m_vVelocity;
	
	FLOAT m_fSpeed;
	FLOAT m_fMass;
	MyRect m_SPRect;	//화면 좌표계 객체의 사각형 : 위치는 중심점이 기준이 된다.
	MyRect m_CSRect;	//충돌 판정을 위한 객체의 사각형 : 위치는 좌상단점이 기준이 된다.
	MyRect m_DRect;		//렌더가 될 NDC좌표를 계산하기 위한 사각형
	MyRect m_tRect;		//텍스처 사각형

	MyRect m_boundary;	//객체의 활동 범위 사각형

public:
	MyObject2D();
	~MyObject2D();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName, wstring wszMaskFileName);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		MyRect pRect, MyRect tRect, MyRect bRect);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskFileName, MyRect pRect, MyRect tRect, MyRect bRect);

	virtual bool postFrame(const MyRect& camRt);
	bool render() override;
	bool release() override;

	void ScreenToView(MyRect& rt, const MyRect& camRt);

	virtual void setPosRect(MyRect rt);
	virtual void setPosRect(MyRect rt, const MyRect& camRt);
	virtual void setTexRect(MyRect rt);
	virtual void setBoundRect(MyRect rt);

	MyRect getPosRect() const;
	MyRect getCollisionRect() const;
	MyRect getTexRect() const;

	MyVector2F getDirection();
	void setDirection(MyVector2F& vDirection);

	void setForce(MyVector2F& vforce);
	MyVector2F getForce();
	void resetVector(MyVector2F& v);
};