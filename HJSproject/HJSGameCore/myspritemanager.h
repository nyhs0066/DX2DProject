#pragma once
#include "mytexturemanager.h"
#include "myshape.h"

using RT_ARRAY = std::vector<MyExRect>;
using TEX_ARRAY = std::vector<MyTexture*>;
using std::vector;

class MySprite
{
public:
	wstring						m_IDname;
	UINT						m_idx;
	wstring						m_RPath;

	RT_ARRAY			m_rtSpriteArray;
	vector<RT_ARRAY>	m_childRtSpriteArray;

	TEX_ARRAY			m_texSpriteArray;
	vector<TEX_ARRAY>	m_childTexSpriteArray;

	MySprite();
	~MySprite();

	bool init();
	bool frame();
	bool render();
	bool release();
};

class MySpriteManager : public Singleton<MySpriteManager>
{
	friend class Singleton<MySpriteManager>;
private:
	vector<RT_ARRAY>		m_tempRtArray;
	vector<TEX_ARRAY>		m_tempTexArray;
	vector<wstring>			m_tempRtSpriteName;
	vector<wstring>			m_tempTexSpriteName;

	vector<wstring>			m_InfoFileNameArray;

	map<wstring, MySprite*> m_spriteMap;

public:
	bool loadSingleTexSprite(std::wifstream& wiFp);
	bool loadMultiTexSprite(std::wifstream& wiFp);

	bool loadSpriteInfoFile(wstring wszInfoFileName);
	bool loadSprites(wstring wszInfoFileName);

	bool init();
	bool frame();
	bool render();
	bool release();

	MySprite* getSprite(wstring wszSpriteName);
};

#define SPRITE_MANAGER MySpriteManager::getInstance()
#define LOAD_SPRITE(wszInfoFileName) SPRITE_MANAGER.loadSprites(wszInfoFileName)
#define GET_SPRITE(wszSpriteName) SPRITE_MANAGER.getSprite(wszSpriteName)
