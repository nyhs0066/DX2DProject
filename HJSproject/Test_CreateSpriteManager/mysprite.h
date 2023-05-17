#pragma once
#include "mytexturemanager.h"
#include "myshape.h"

using RT_ARRAY = std::vector<MyRect>;
using TEX_ARRAY = std::vector<MyTexture*>;
using std::vector;

class MySingleTextureSprite
{
public:
	wstring m_wszName;
	RT_ARRAY m_spriteArray;
	vector<RT_ARRAY> m_childSpriteArray;

	MySingleTextureSprite();
	~MySingleTextureSprite();

	bool init();
	bool frame();
	bool render();
	bool release();
};

class MyMultiTextureSprite
{
public:
	wstring m_wszName;
	TEX_ARRAY m_spriteArray;
	vector<TEX_ARRAY> m_childSpriteArray;

	MyMultiTextureSprite();
	~MyMultiTextureSprite();

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
	vector<wstring>			m_tempSpriteName;

	vector<wstring>			m_STInfoFileNameArray;
	vector<wstring>			m_MTInfoFileNameArray;

	map<wstring, MySingleTextureSprite*>	m_singleTexSpriteMap;
	map<wstring, MyMultiTextureSprite*>		m_multiTexSpriteMap;

public :
	bool loadSingleTexSpriteInfoFile(wstring wszInfoFileName);
	bool loadSingleTexSprites(wstring wszInfoFileName);

	bool loadMultiTexSpriteInfoFile(wstring wszInfoFileName);
	bool loadMultiTexSprites(wstring wszInfoFileName);

	bool init();
	bool frame();
	bool render();
	bool release();

	MySingleTextureSprite* getSingleTexSprite(wstring wszSpriteName);
	MyMultiTextureSprite* getMultiTexSprite(wstring wszSpriteName);
};

#define SPRITE_MANAGER MySpriteManager::getInstance()
#define LOAD_ST_SPRITE(wszInfoFileName) SPRITE_MANAGER.loadSingleTexSprites(wszInfoFileName)
#define LOAD_MT_SPRITE(wszInfoFileName) SPRITE_MANAGER.loadMultiTexSprites(wszInfoFileName)

#define GET_ST_SPRITE(wszSpriteName) SPRITE_MANAGER.getSingleTexSprite(wszSpriteName)
#define GET_MT_SPRITE(wszSpriteName) SPRITE_MANAGER.getMultiTexSprite(wszSpriteName)