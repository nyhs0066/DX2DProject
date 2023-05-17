#pragma once
#include "mybaseobject.h"
#include "myshape.h"
#include "mycollision.h"

class MyObject2D : public MyBaseObject
{
protected:
	MyVector2F m_vDirection;		//���� ����
	MyVector2F m_vForce;			//��
	MyVector2F m_vAcceleration;		//���ӵ�
	MyVector2F m_vVelocity;			//�ӵ�

	MyRect m_DRect;		//������ �� ��ġ�� NDC��ǥ�� ����ϱ� ���� �簢��
	MyRect m_DTexRect;		//������ �� �ؽ�ó�� �� NDC��ǥ�� ����ϱ� ���� �簢��

	MyRect m_CSRect;	//�浹 ������ ���� ��ü�� �簢�� : ��ġ�� �»������ ������ �ȴ�.

public:
	MyTexture* m_pMaskTexture;		//����ũ �ؽ���

	FLOAT m_fSpeed;		//���׷��� ������� �ʴ� �ӷ�
	FLOAT m_fMass;		//�ӵ��� ������ ����

	MyRect m_SPRect;	//ȭ�� ��ǥ�� ��ü�� �簢�� : ��ġ�� �߽����� ������ �ȴ�.
	MyRect m_TRect;		//�ؽ�ó �簢��
	MyRect m_BRect;		//��ü�� Ȱ�� ���� �簢��

	MyVector2F m_posOffset;

	//��ü ��������
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

	//ī�޶� ���� ��ġ ������ �ʿ��� ��ü�� ���� ������ ��ó��
	virtual bool postFrame(const MyRect& camRt, FLOAT radian = 0.0f);
	bool render() override;
	bool release() override;

	void ScreenToView(MyRect& rt, const MyRect& camRt);

	//��ü�� �ִ� Ȱ������ ������ �ʿ��� ��� ���
	virtual bool boundaryCheck();

	//��ü�� �浹�� ó���ϱ� ���� �ڵ鷯
	virtual MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);

	//��ü �Ӽ��� ��� ���� �Լ�
	MyRect getCSRect() const;
	MyVector2F getDirection();
	MyVector2F getForce();

	//��ü �Ӽ� ������ ���� �Լ�
	virtual void setPosRect(MyRect rt);
	virtual void setPosRect(MyRect rt, const MyRect& camRt);
	virtual void setTexRect(MyRect rt);
	virtual void setBoundRect(MyRect rt);
	void setDirection(MyVector2F& vDirection);
	void setForce(MyVector2F& vforce);

	//��ü ��ġ ȸ�� �� �̹��� ȸ���� ���� ���� �Լ�
	void texRotation(FLOAT radian);							//���ڸ� ȸ�� : NDC���� ó��
	void arbitRotation(MyVector2F pivot, FLOAT radian);		//������ �˵� ȸ�� : ���� ��ǥ���� ó��
};