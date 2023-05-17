#pragma once
#include "mybaseobject.h"
#include "myshape.h"
#include "mycollision.h"

class MyObject2D : public MyBaseObject
{
protected:
	MyVector2F m_vDirection;		//방향 벡터
	MyVector2F m_vForce;			//힘
	MyVector2F m_vAcceleration;		//가속도
	MyVector2F m_vVelocity;			//속도

	MyRect m_DRect;		//렌더가 될 위치의 NDC좌표를 계산하기 위한 사각형
	MyRect m_DTexRect;		//렌더가 될 텍스처의 의 NDC좌표를 계산하기 위한 사각형

	MyRect m_CSRect;	//충돌 판정을 위한 객체의 사각형 : 위치는 좌상단점이 기준이 된다.

public:
	MyTexture* m_pMaskTexture;		//마스크 텍스쳐

	FLOAT m_fSpeed;		//저항력이 적용되지 않는 속력
	FLOAT m_fMass;		//속도에 적용할 질량

	MyRect m_SPRect;	//화면 좌표계 객체의 사각형 : 위치는 중심점이 기준이 된다.
	MyRect m_TRect;		//텍스처 사각형
	MyRect m_BRect;		//객체의 활동 범위 사각형

	MyVector2F m_posOffset;

	//객체 설정값들
	FLOAT m_fAngle;
	FLOAT m_fAttackSpeed;
	INT m_iMaxHitPoint;
	INT m_iCurHitPoint;
	
	INT m_iDamage;

	MyObject2D();
	virtual ~MyObject2D();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		MyRect pRect = {0.0f, 0.0f, 0.0f, 0.0f},
		MyRect bRect = { 0.0f, 0.0f, 0.0f, 0.0f });
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskFileName, 
		MyRect pRect = { 0.0f, 0.0f, 0.0f, 0.0f },
		MyRect bRect = { 0.0f, 0.0f, 0.0f, 0.0f });

	//카메라에 의한 위치 보정이 필요한 객체가 쓰는 프레임 후처리
	virtual bool postFrame(const MyRect& camRt, FLOAT radian = 0.0f);
	bool render() override;
	bool release() override;

	void ScreenToView(MyRect& rt, const MyRect& camRt);

	//객체의 최대 활동영역 제한이 필요한 경우 사용
	virtual bool boundaryCheck();

	//객체의 충돌을 처리하기 위한 핸들러
	virtual MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);

	//객체 속성을 얻기 위한 함수
	MyRect getCSRect() const;
	MyVector2F getDirection();
	MyVector2F getForce();

	//객체 속성 설정을 위한 함수
	virtual void setPosRect(MyRect rt);
	virtual void setPosRect(MyRect rt, const MyRect& camRt);
	virtual void setTexRect(MyRect rt);
	virtual void setBoundRect(MyRect rt);
	void setDirection(MyVector2F& vDirection);
	void setForce(MyVector2F& vforce);

	//객체 위치 회전 및 이미지 회전을 위한 보조 함수
	void texRotation(FLOAT radian);							//제자리 회전 : NDC에서 처리
	void arbitRotation(MyVector2F pivot, FLOAT radian);		//기준점 궤도 회전 : 월드 좌표에서 처리
};