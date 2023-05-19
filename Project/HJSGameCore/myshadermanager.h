#pragma once
#include "mydxdevicemanager.h"

#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")

using std::map;
using std::wstring;

class MyShader
{
public:
	wstring m_shaderName;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pVShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pPShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pVertexLayout;

	Microsoft::WRL::ComPtr<ID3DBlob>					m_pVSCode;
	Microsoft::WRL::ComPtr<ID3DBlob>					m_pPSCode;

private:
	Microsoft::WRL::ComPtr<ID3DBlob>					m_pErrCode;

	HRESULT createVShader(wstring wszFileName);
	HRESULT createPShader(wstring wszFileName);
	HRESULT createVertexLayout();

public:

	MyShader();
	~MyShader();

	HRESULT create(wstring wszFileName);

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
	MyShader* load(wstring wszFileName);
	bool loadDir(wstring wszDirName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define SHADER_MANAGER				MyShaderManager::getInstance()
#define LOAD_SHADER(wszFileName)	MyShaderManager::getInstance().load(wszFileName)
#define LOAD_SHADER_DIR(wszDirName) MyShaderManager::getInstance().loadDir(wszDirName)