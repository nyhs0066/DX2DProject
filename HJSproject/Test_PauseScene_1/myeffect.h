#pragma once
#include "myspritemanager.h"
#include "myobject2d.h"

class MyEffect
{
public:
	static std::unique_ptr<MyObject2D> g_pDrawObj;

	MySprite* m_pSprite;

	//스프라이트 프리셋
	vector<MyEffect*> m_pCreateEPresets;		//생성시 이펙트 생성을 위한 이펙트 프리셋
	vector<MyEffect*> m_pDestructEPresets;		//소멸시 이펙트 생성을 위한 이펙트 프리셋
	vector<MyEffect*> m_pEventEPresets;			//개별 이벤트용 이펙트 프리셋

	//사용할 쉐이더와 텍스처 이름
	wstring m_wszShaderName;
	wstring m_wszTexName;
	MyTexture* m_pMaskTexture;

	//이펙트 수명 처리와 스프라이트 애니메이션을 위한 변수
	FLOAT		m_fLifeSpanT;		//지속시간
	FLOAT		m_fplayT;			//스프라이트 애니메이션 1회전 시간
	FLOAT		m_fStepT;			//스프라이트 교체 시간

	//이펙트 소유
	FLOAT		m_fTimer;			//스프라이트 교체를 위한 시간 누적 변수
	FLOAT		m_fElapseT;			//이펙트 생성후 경과시간
	UINT		m_iCuridx;			//이펙트의 현재 스프라이트 인덱스 번호
	BOOL		m_LifeFlag;			//이펙트 소멸 여부

	//이펙트 사각형과 색상 : 공용으로 사용하는 그리기 MyObject2D객체에 그릴 때 넘겨주거나 충돌시 충돌 판정함수에 넘겨준다.
	MyRect m_SPRect;			//위치 사각형
	MyRect m_TRect;				//텍스처 사각형
	MyRect m_CSRect;			//충돌 판정 사각형
	MyRect m_BRect;				//경계 영역 사각형
	MyVector4F m_color;			//색상

	//방향과 속도
	MyVector2F m_vDirection;		//방향벡터
	FLOAT m_fSpeed;				//속도
	FLOAT m_fRotateAnglePerSec;		//회전 각 속도(라디안)
	
	//이펙트 객체가 가지는 데미지
	INT m_iDamage;

	MyEffect();
	~MyEffect();

	bool create(wstring wszShaderName, wstring wszTexName, wstring wszSpriteName);
	bool create(wstring wszShaderName, wstring wszTexName,
		wstring wszMaskName, wstring wszSpriteName);

	virtual bool update();
	virtual void setPosRect(MyRect posRt);
	virtual void setTimeProperty(FLOAT fLifeSpanT = 1.0f, FLOAT fPlayT = 1.0f);
	virtual void setDirectionAndSpeed(MyVector2F vDirection = {0.0f, 0.0f}, FLOAT fSpeed = 0.0f, FLOAT fRotateSpeed = 0.0f);

	virtual bool preRender(const MyRect& camRt);

	virtual bool release();
};

class MyProjectile : public MyEffect
{
public:
	bool update() override;
};
