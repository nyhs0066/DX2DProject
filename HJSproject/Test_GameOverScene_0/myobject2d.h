#pragma once
#include "mybaseobject.h"
#include "myshape.h"
#include "mycollision.h"
#include "myeffect.h"

#define FIXFRAMET 1.0f / 60.0f

class MyEffect;

class MyObject2D : public MyBaseObject
{
protected:
	MyVector2F m_vDirection;		//방향 벡터
	MyVector2F m_vForce;			//힘
	MyVector2F m_vAcceleration;		//가속도
	MyVector2F m_vVelocity;			//속도

	//그리기 사각형들은 네개의 점으로 구성된다.
	MyExRect m_DRect;			//렌더가 될 위치의 NDC좌표를 계산하기 위한 사각형
	MyExRect m_DTexRect;		//렌더가 될 텍스처의 의 NDC좌표를 계산하기 위한 사각형

	MyExRect m_CSRect;	//충돌 판정을 위한 객체의 사각형 : 위치는 좌상단점이 기준이 된다.

public:
	MyTexture* m_pMaskTexture;		//마스크 텍스쳐

	FLOAT m_fSpeed;		//저항력이 적용되지 않는 속력
	FLOAT m_fMass;		//속도에 적용할 질량

	MyExRect m_SPRect;	//화면 좌표계 객체의 사각형 : 위치는 중심점이 기준이 된다.
	MyExRect m_TRect;		//텍스처 사각형
	MyExRect m_BRect;		//객체의 활동 범위 사각형

	MyVector2F m_posOffset;

	//객체 설정값들
	FLOAT m_fAngle;
	FLOAT m_fAttackSpeed;
	FLOAT m_fAttackTimer;
	INT m_iMaxHitPoint;
	INT m_iCurHitPoint;
	
	INT m_iDamage;

	MyObject2D();
	virtual ~MyObject2D();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		MyExRect pRect = {0.0f, 0.0f, 0.0f, 0.0f},
		MyExRect bRect = { 0.0f, 0.0f, 0.0f, 0.0f });
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskFileName, 
		MyExRect pRect = { 0.0f, 0.0f, 0.0f, 0.0f },
		MyExRect bRect = { 0.0f, 0.0f, 0.0f, 0.0f });

	//카메라에 의한 위치 보정이 필요한 객체가 쓰는 프레임 후처리
	virtual bool postFrame(const MyExRect& camRt, FLOAT radian = 0.0f);
	virtual bool postFrame(FLOAT radian = 0.0f);

	bool render() override;
	bool release() override;

	void ScreenToView(MyExRect& rt, const MyExRect& camRt);

	//객체의 최대 활동영역 제한이 필요한 경우 사용
	virtual bool boundaryCheck();

	//객체의 충돌을 처리하기 위한 핸들러
	virtual MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt);

	//객체 속성을 얻기 위한 함수
	MyExRect getCSRect() const;
	MyVector2F getDirection();
	MyVector2F getForce();

	//객체 속성 설정을 위한 함수
	virtual void setPosRect(MyExRect rt);
	virtual void setTexRect(MyExRect rt);
	virtual void setBoundRect(MyExRect rt);
	void setDirection(MyVector2F& vDirection);
	void setForce(MyVector2F& vforce);

	//객체 위치 회전 및 이미지 회전을 위한 보조 함수
	void texRotation(FLOAT radian);							//제자리 회전 : NDC에서 처리
	void arbitRotation(MyVector2F pivot, FLOAT radian);		//기준점 궤도 회전 : 월드 좌표에서 처리

	//중점좌표를 사용하는 사각형 객체들을 위한 충돌 사각형 업데이트 함수
	//이걸 오버라이드 하면 히트박스 크기를 조절 할 수 있다.
	virtual void adjustCRect(MyExRect& rt);

	//버퍼 업데이트 함수
	bool updateVertexBuffer() override;

	//객체 고유의 이펙트 생성과 등록 함수
	virtual void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget) {};
};