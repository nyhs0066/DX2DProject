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
	MyVector2F m_vDirection;		//���� ����
	MyVector2F m_vForce;			//��
	MyVector2F m_vAcceleration;		//���ӵ�
	MyVector2F m_vVelocity;			//�ӵ�

	//�׸��� �簢������ �װ��� ������ �����ȴ�.
	MyExRect m_DRect;			//������ �� ��ġ�� NDC��ǥ�� ����ϱ� ���� �簢��
	MyExRect m_DTexRect;		//������ �� �ؽ�ó�� �� NDC��ǥ�� ����ϱ� ���� �簢��

	MyExRect m_CSRect;	//�浹 ������ ���� ��ü�� �簢�� : ��ġ�� �»������ ������ �ȴ�.

public:
	MyTexture* m_pMaskTexture;		//����ũ �ؽ���

	FLOAT m_fSpeed;		//���׷��� ������� �ʴ� �ӷ�
	FLOAT m_fMass;		//�ӵ��� ������ ����

	MyExRect m_SPRect;	//ȭ�� ��ǥ�� ��ü�� �簢�� : ��ġ�� �߽����� ������ �ȴ�.
	MyExRect m_TRect;		//�ؽ�ó �簢��
	MyExRect m_BRect;		//��ü�� Ȱ�� ���� �簢��

	MyVector2F m_posOffset;

	//��ü ��������
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

	//ī�޶� ���� ��ġ ������ �ʿ��� ��ü�� ���� ������ ��ó��
	virtual bool postFrame(const MyExRect& camRt, FLOAT radian = 0.0f);
	virtual bool postFrame(FLOAT radian = 0.0f);

	bool render() override;
	bool release() override;

	void ScreenToView(MyExRect& rt, const MyExRect& camRt);

	//��ü�� �ִ� Ȱ������ ������ �ʿ��� ��� ���
	virtual bool boundaryCheck();

	//��ü�� �浹�� ó���ϱ� ���� �ڵ鷯
	virtual MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyExRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyEffect* pCObj, const MyExRect& instRt);

	//��ü �Ӽ��� ��� ���� �Լ�
	MyExRect getCSRect() const;
	MyVector2F getDirection();
	MyVector2F getForce();

	//��ü �Ӽ� ������ ���� �Լ�
	virtual void setPosRect(MyExRect rt);
	virtual void setTexRect(MyExRect rt);
	virtual void setBoundRect(MyExRect rt);
	void setDirection(MyVector2F& vDirection);
	void setForce(MyVector2F& vforce);

	//��ü ��ġ ȸ�� �� �̹��� ȸ���� ���� ���� �Լ�
	void texRotation(FLOAT radian);							//���ڸ� ȸ�� : NDC���� ó��
	void arbitRotation(MyVector2F pivot, FLOAT radian);		//������ �˵� ȸ�� : ���� ��ǥ���� ó��

	//������ǥ�� ����ϴ� �簢�� ��ü���� ���� �浹 �簢�� ������Ʈ �Լ�
	//�̰� �������̵� �ϸ� ��Ʈ�ڽ� ũ�⸦ ���� �� �� �ִ�.
	virtual void adjustCRect(MyExRect& rt);

	//���� ������Ʈ �Լ�
	bool updateVertexBuffer() override;

	//��ü ������ ����Ʈ ������ ��� �Լ�
	virtual void createEffect(MyEffect* pEffectPreset, std::list<MyEffect*>& effectList, MyObject2D* pTarget) {};
};