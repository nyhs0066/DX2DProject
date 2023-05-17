#pragma once
#include "mydxdevice.h"

class MyTexture
{
protected:
	ID3D11Texture2D*			m_pTexResource;
	ID3D11ShaderResourceView*	m_pSRView;
	D3D11_TEXTURE2D_DESC		m_tex2dDesc;
	wstring						m_szfileName;

	HRESULT createTexResourceAndView(wstring fileName);
public:
	MyTexture();
	~MyTexture();

	bool create(wstring wszfileName);

	ID3D11ShaderResourceView* getSRView();

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

public:
	MyTexture* loadTexture(wstring wszfileName);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define LOAD_TEXTURE(wszfileName) MyTextureManager::getInstance().loadTexture((wszfileName))