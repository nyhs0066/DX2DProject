#pragma once
#include "myspritemanager.h"
#include "myobject2d.h"

class MyEffect
{
public:
	static std::unique_ptr<MyObject2D> g_pDrawObj;

	MySprite* m_pSprite;

	//��������Ʈ ������
	vector<MyEffect*> m_pCreateEPresets;		//������ ����Ʈ ������ ���� ����Ʈ ������
	vector<MyEffect*> m_pDestructEPresets;		//�Ҹ�� ����Ʈ ������ ���� ����Ʈ ������
	vector<MyEffect*> m_pEventEPresets;			//���� �̺�Ʈ�� ����Ʈ ������

	//����� ���̴��� �ؽ�ó �̸�
	wstring m_wszShaderName;
	wstring m_wszTexName;
	MyTexture* m_pMaskTexture;

	//����Ʈ ���� ó���� ��������Ʈ �ִϸ��̼��� ���� ����
	FLOAT		m_fLifeSpanT;		//���ӽð�
	FLOAT		m_fplayT;			//��������Ʈ �ִϸ��̼� 1ȸ�� �ð�
	FLOAT		m_fStepT;			//��������Ʈ ��ü �ð�

	//����Ʈ ����
	FLOAT		m_fTimer;			//��������Ʈ ��ü�� ���� �ð� ���� ����
	FLOAT		m_fElapseT;			//����Ʈ ������ ����ð�
	UINT		m_iCuridx;			//����Ʈ�� ���� ��������Ʈ �ε��� ��ȣ
	BOOL		m_LifeFlag;			//����Ʈ �Ҹ� ����

	//����Ʈ �簢���� ���� : �������� ����ϴ� �׸��� MyObject2D��ü�� �׸� �� �Ѱ��ְų� �浹�� �浹 �����Լ��� �Ѱ��ش�.
	MyRect m_SPRect;			//��ġ �簢��
	MyRect m_TRect;				//�ؽ�ó �簢��
	MyRect m_CSRect;			//�浹 ���� �簢��
	MyRect m_BRect;				//��� ���� �簢��
	MyVector4F m_color;			//����

	//����� �ӵ�
	MyVector2F m_vDirection;		//���⺤��
	FLOAT m_fSpeed;				//�ӵ�
	FLOAT m_fRotateAnglePerSec;		//ȸ�� �� �ӵ�(����)
	
	//����Ʈ ��ü�� ������ ������
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
