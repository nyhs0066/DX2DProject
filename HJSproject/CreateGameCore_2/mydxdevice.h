#pragma once
#include "myunih.h"

class MyDXDevice : public Singleton<MyDXDevice>
{
	friend class Singleton<MyDXDevice>;
private:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDContext;

	MyDXDevice();
	~MyDXDevice();
public:
	bool create();
	bool init();
	bool release();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDContext();
};

#define I_DEVICE MyDXDevice::getInstance().getDevice()
#define I_DCONTEXT MyDXDevice::getInstance().getDContext()