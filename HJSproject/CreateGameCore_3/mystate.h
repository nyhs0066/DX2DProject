#pragma once
#include "mydxdevice.h"

class MyState : public Singleton<MyState>
{
	friend class Singleton<MyState>;
private:
	ID3D11SamplerState* m_pSamplerState;
	ID3D11BlendState* m_pBlendState;

	MyState();
	~MyState();

	HRESULT createSmpState();
	HRESULT createBlendState();

public:
	bool create();

	bool init();
	bool frame();
	bool render();
	bool release();

	ID3D11SamplerState* getSamplerState();
	ID3D11BlendState* getBlendState();
};

#define I_SAMPLERSTATE MyState::getInstance().getSamplerState()
#define I_BLENDSTATE MyState::getInstance().getBlendState()