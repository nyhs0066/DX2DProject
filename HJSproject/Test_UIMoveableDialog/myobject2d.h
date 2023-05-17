#pragma once
#include "mybaseobject.h"
#include "myshape.h"
#include "mycollision.h"

class MyObject2D : public MyBaseObject
{
protected:
	MyTexture* m_pMaskTexture;		//����ũ �ؽ���

	MyVector2F m_vDirection;		//���� ����
	MyVector2F m_vForce;			//��
	MyVector2F m_vAcceleration;		//���ӵ�
	MyVector2F m_vVelocity;			//�ӵ�
	
	FLOAT m_fSpeed;		//���׷��� ������� �ʴ� �ӷ�
	FLOAT m_fMass;		//�ӵ��� ������ ����
	MyRect m_SPRect;	//ȭ�� ��ǥ�� ��ü�� �簢�� : ��ġ�� �߽����� ������ �ȴ�.
	MyRect m_CSRect;	//�浹 ������ ���� ��ü�� �簢�� : ��ġ�� �»������ ������ �ȴ�.
	MyRect m_DRect;		//������ �� NDC��ǥ�� ����ϱ� ���� �簢��
	MyRect m_TRect;		//�ؽ�ó �簢��

	MyRect m_boundary;	//��ü�� Ȱ�� ���� �簢��

public:
	MyVector2F m_posOffset;

	//��ü ��������
	FLOAT m_fAttackSpeed;	
	INT m_iHitPoint;
	INT m_iMaxHitPoint;
	INT m_iDamage;

	MyObject2D();
	virtual ~MyObject2D();

	bool create(wstring wszShaderFileName, wstring wszTextureFileName);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName, wstring wszMaskFileName);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		MyRect pRect, MyRect tRect, MyRect bRect);
	bool create(wstring wszShaderFileName, wstring wszTextureFileName,
		wstring wszMaskFileName, MyRect pRect, MyRect tRect, MyRect bRect);

	//ī�޶� ���� ��ġ ������ �ʿ��� ��ü�� ���� ������ ��ó��
	virtual bool postFrame(const MyRect& camRt);
	bool render() override;
	bool release() override;

	void ScreenToView(MyRect& rt, const MyRect& camRt);

	//��ü�� �ִ� Ȱ������ ������ �ʿ��� ��� ���
	virtual bool boundaryCheck();

	//��ü�� �浹�� ó���ϱ� ���� �ڵ鷯
	virtual MyVector2F staticCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);
	virtual MyVector2F dynamicCollisionHandler(const MyObject2D* pCObj, const MyRect& instRt);

	//��ü �Ӽ��� ��� ���� �Լ�
	MyRect getPosRect() const;
	MyRect getCollisionRect() const;
	MyRect getTexRect() const;
	MyVector2F getDirection();
	MyVector2F getForce();

	//��ü �Ӽ� ������ ���� �Լ�
	virtual void setPosRect(MyRect rt);
	virtual void setPosRect(MyRect rt, const MyRect& camRt);
	virtual void setTexRect(MyRect rt);
	virtual void setBoundRect(MyRect rt);
	void setDirection(MyVector2F& vDirection);
	void setForce(MyVector2F& vforce);
};