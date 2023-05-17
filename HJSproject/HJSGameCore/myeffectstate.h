#pragma once
#include "mydxdevicemanager.h"

class MyEffectState : public Singleton<MyEffectState>
{
	friend class Singleton<MyEffectState>;
private:
	MyEffectState();
	~MyEffectState();

	//create sampler states
	HRESULT createSStateWrapPoint();
	HRESULT createSStateBorderPoint();

	//create rasterizer states
	HRESULT createRStateWireFrame();
	HRESULT createRStateSolid();

	//create blend states
	HRESULT createBStateDefault();
	HRESULT createBStateAlphaBlending();
public:
	//Sampler States
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSStateWrapPoint;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSStateBorderPoint;

	//Rasterizer States
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRStateWireFrame;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRStateSolid;

	////Blend State
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_pBStateDefault;			//미설정시 기본으로 렌더 타겟 0번에 설정되는 값
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_pBStateAlphaBlend;

	////Depth-Stencil State
	//static ID3D11DepthStencilState* m_pDState;

	HRESULT create();
	
	bool init();
	bool frame();
	bool render();
	bool release();
};

#define EFFECT_STATE MyEffectState::getInstance()