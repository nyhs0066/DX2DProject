#include "mysprite.h"

MySingleTextureSprite::MySingleTextureSprite()
{
}

MySingleTextureSprite::~MySingleTextureSprite()
{
	release();
}

bool MySingleTextureSprite::init()
{
	return true;
}

bool MySingleTextureSprite::frame()
{
	return true;
}

bool MySingleTextureSprite::render()
{
	return true;
}

bool MySingleTextureSprite::release()
{
	m_spriteArray.clear();
	m_childSpriteArray.clear();

	return true;
}

MyMultiTextureSprite::MyMultiTextureSprite()
{
}

MyMultiTextureSprite::~MyMultiTextureSprite()
{
	release();
}

bool MyMultiTextureSprite::init()
{
	return true;
}

bool MyMultiTextureSprite::frame()
{
	return true;
}

bool MyMultiTextureSprite::render()
{
	return true;
}

bool MyMultiTextureSprite::release()
{
	m_spriteArray.clear();
	m_childSpriteArray.clear();

	return true;
}


bool MySpriteManager::loadSingleTexSpriteInfoFile(wstring wszInfoFileName)
{
	if (std::find(m_STInfoFileNameArray.begin(), m_STInfoFileNameArray.end(), wszInfoFileName) != m_STInfoFileNameArray.end())
	{
		return false;
	}

	std::wifstream wiFp;
	std::wstring wszbuf;

	wiFp.open(wszInfoFileName, std::ios::in);
	if (!wiFp) { return false; }

	wszbuf.resize(256);

	UINT spriteNum;
	UINT rtNum;
	MyRect rect;
	
	wiFp >> wszbuf >> spriteNum;
	m_tempRtArray.resize(spriteNum);

	for(UINT i = 0; i < spriteNum; i++)
	{
		wiFp >> wszbuf;
		if (wszbuf == L"END") { break; }
		m_tempSpriteName.push_back(wszbuf);
		wiFp >> rtNum;

		for (UINT j = 0; j < rtNum; j++)
		{ 
			wiFp >> rect.v[0] >> rect.v[1] >> rect.v[2] >> rect.v[3];
			m_tempRtArray[i].push_back(rect);
		}
	}

	m_STInfoFileNameArray.push_back(wszInfoFileName);

	return true;
}

bool MySpriteManager::loadSingleTexSprites(wstring wszInfoFileName)
{
	m_tempRtArray.clear();
	m_tempSpriteName.clear();

	if (!loadSingleTexSpriteInfoFile(wszInfoFileName)) { return false; }

	for (int i = 0; i < m_tempRtArray.size(); i++)
	{
		if (m_singleTexSpriteMap.find(m_tempSpriteName[i]) == m_singleTexSpriteMap.end())
		{
			MySingleTextureSprite* newE = new MySingleTextureSprite;
			newE->m_wszName = m_tempSpriteName[i];
			newE->m_spriteArray = m_tempRtArray[i];

			m_singleTexSpriteMap.insert(std::make_pair(m_tempSpriteName[i], newE));
		}
	}

	return true;
}

bool MySpriteManager::loadMultiTexSpriteInfoFile(wstring wszInfoFileName)
{
	if (std::find(m_MTInfoFileNameArray.begin(), m_MTInfoFileNameArray.end(), wszInfoFileName) != m_MTInfoFileNameArray.end())
	{
		return false;
	}

	std::wifstream wiFp;
	std::wstring wszbuf;
	std::wstring filePath;
	std::wstring extention;

	std::wstring name;
	std::wstring path;

	wiFp.open(wszInfoFileName, std::ios::in);
	if (!wiFp) { return false; }

	wszbuf.resize(256);
	filePath.resize(256);
	extention.resize(256);
	name.resize(256);
	path.resize(256);

	UINT spriteNum;
	UINT texListNum;
	MyTexture* tex;

	wiFp >> wszbuf >> spriteNum;
	m_tempTexArray.resize(spriteNum);
	wiFp >> wszbuf >> filePath;
	wiFp >> wszbuf >> extention;
	wiFp >> wszbuf >> wszbuf >> wszbuf;

	for (UINT i = 0; i < spriteNum; i++)
	{
		wiFp >> wszbuf;
		if (wszbuf == L"END") { break; }
		m_tempSpriteName.push_back(wszbuf);
		wiFp >> name >> texListNum;

		for (UINT j = 0; j < texListNum; j++)
		{
			path = filePath + name + std::to_wstring(j) + extention;
			tex = LOAD_TEXTURE(path);
			if (!tex) { return false; }
			m_tempTexArray[i].push_back(tex);
		}
	}

	m_MTInfoFileNameArray.push_back(wszInfoFileName);

	return true;
}

bool MySpriteManager::loadMultiTexSprites(wstring wszInfoFileName)
{
	m_tempTexArray.clear();
	m_tempSpriteName.clear();

	if (!loadMultiTexSpriteInfoFile(wszInfoFileName)) { return false; }

	for (int i = 0; i < m_tempTexArray.size(); i++)
	{
		if (m_multiTexSpriteMap.find(m_tempSpriteName[i]) == m_multiTexSpriteMap.end())
		{
			MyMultiTextureSprite* newE = new MyMultiTextureSprite;
			newE->m_wszName = m_tempSpriteName[i];
			newE->m_spriteArray = m_tempTexArray[i];

			m_multiTexSpriteMap.insert(std::make_pair(m_tempSpriteName[i], newE));
		}
	}

	return true;
}

bool MySpriteManager::init()
{
	return true;
}

bool MySpriteManager::frame()
{
	return true;
}

bool MySpriteManager::render()
{
	return true;
}

bool MySpriteManager::release()
{
	for (map<wstring, MySingleTextureSprite*>::iterator::value_type it : m_singleTexSpriteMap)
	{
		delete it.second;
		it.second = nullptr;
	}

	for (map<wstring, MyMultiTextureSprite*>::iterator::value_type it : m_multiTexSpriteMap)
	{
		delete it.second;
		it.second = nullptr;
	}

	m_singleTexSpriteMap.clear();
	m_STInfoFileNameArray.clear();

	m_multiTexSpriteMap.clear();
	m_MTInfoFileNameArray.clear();

	return true;
}

MySingleTextureSprite* MySpriteManager::getSingleTexSprite(wstring wszSpriteName)
{
	map<wstring, MySingleTextureSprite*>::iterator it = m_singleTexSpriteMap.find(wszSpriteName);
	if (it != m_singleTexSpriteMap.end()) { return it->second; }
	else { return nullptr; }
}

MyMultiTextureSprite* MySpriteManager::getMultiTexSprite(wstring wszSpriteName)
{
	map<wstring, MyMultiTextureSprite*>::iterator it = m_multiTexSpriteMap.find(wszSpriteName);
	if (it != m_multiTexSpriteMap.end()) { return it->second; }
	else { return nullptr; }
}