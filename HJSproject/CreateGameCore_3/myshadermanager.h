#pragma once
#include "mydxdevice.h"

class MyShader
{
protected:
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
	wstring					m_szfileName;

	ID3DBlob*				m_pVScode;
	ID3DBlob*				m_pPScode;

	HRESULT					createVertexLayout();
	HRESULT					createVShader(wstring wszFileName);
	HRESULT					createPShader(wstring wszFileName);

public:
	MyShader();
	~MyShader();

	bool create(wstring wszFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

class MyShaderManager : public Singleton<MyShaderManager>
{
	friend class Singleton<MyShaderManager>;
private:
	map<wstring, MyShader*> m_shaderMap;

	MyShaderManager();
	~MyShaderManager();

public:
	MyShader* loadShader(wstring wszFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define LOAD_SHADER(wszFileName) MyShaderManager::getInstance().loadShader(wszFileName)