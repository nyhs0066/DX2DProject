#pragma once
#include "mydxdevicemanager.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "myshape.h"

#pragma comment (lib, "DirectXTK.lib")

//#ifdef _DEBUG
//#pragma comment (lib, "DirectXTK_d.lib")
//#else
//#pragma comment (lib, "DirectXTK_r.lib")
//#endif //_DEBUG

using std::wstring;
using std::map;

class MyTexture
{
public:
	wstring						m_IDname;
	UINT						m_idx;
	wstring						m_RPath;

	D3D11_TEXTURE2D_DESC		m_TextureDesc;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSRView;

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pTextureBuf;

	HRESULT LoadTextureAndCreateSRView(wstring wszFileName);

public:
	MyTexture();
	~MyTexture();

	HRESULT create(wstring wszFileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

class MyTextureManager : public Singleton<MyTextureManager>
{
	friend class Singleton<MyTextureManager>;
private:
	map<wstring, MyTexture*> m_textureMap;

	MyTextureManager();
	~MyTextureManager();

public:
	bool init();
	bool render();
	bool frame();
	bool release();

	MyTexture* load(wstring wszFileName);
	bool loadDir(wstring wszDirName);
};

#define TEXTURE_MANAGER					MyTextureManager::getInstance()
#define LOAD_TEXTURE(wszFileName)		MyTextureManager::getInstance().load(wszFileName)
#define LOAD_TEXTURE_DIR(wszDirName)	MyTextureManager::getInstance().loadDir(wszDirName)
