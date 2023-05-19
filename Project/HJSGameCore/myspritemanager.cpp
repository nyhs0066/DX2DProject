#include "myspritemanager.h"

MySprite::MySprite()
{
	m_idx = 0;
}

MySprite::~MySprite()
{
	release();
}

bool MySprite::init()
{
	return true;
}

bool MySprite::frame()
{
	return true;
}

bool MySprite::render()
{
	return true;
}

bool MySprite::release()
{
	m_rtSpriteArray.clear();
	m_childRtSpriteArray.clear();
	m_texSpriteArray.clear();
	m_childTexSpriteArray.clear();

	return true;
}

bool MySpriteManager::loadSingleTexSprite(std::wifstream& wiFp)
{
	std::wstring wszbuf;
	wszbuf.resize(256);

	UINT spriteNum;
	MyExRect rect;

	RT_ARRAY newArr;
	
	wiFp >> spriteNum >> wszbuf;
	if (!LOAD_TEXTURE(wszbuf.c_str())) { return false; }

	for (UINT i = 0; i < spriteNum; i++)
	{
		wiFp >> rect.v[0] >> rect.v[1] >> rect.v[2] >> rect.v[3];
		newArr.push_back(rect);
	}

	m_tempRtArray.push_back(newArr);

	return true;
}

bool MySpriteManager::loadMultiTexSprite(std::wifstream& wiFp)
{
	std::wstring wszbuf;
	std::wstring filePath;
	std::wstring extention;

	std::wstring name;
	std::wstring path;

	wszbuf.resize(256);
	filePath.resize(256);
	extention.resize(256);
	name.resize(256);
	path.resize(256);

	UINT texListNum;
	MyTexture* tex;

	wiFp >> wszbuf >> filePath;
	wiFp >> wszbuf >> extention;
	
	while (true)
	{
		wiFp >> wszbuf;
		if (wszbuf == L"#END") { break; }
		m_tempTexSpriteName.push_back(wszbuf);

		TEX_ARRAY newArr;
		wiFp >> texListNum;
		
		for (UINT j = 0; j < texListNum; j++)
		{
			wiFp >> name;
			path = filePath + name + extention;
			tex = LOAD_TEXTURE(path);
			if (!tex) { return false; }
			newArr.push_back(tex);
		}
		m_tempTexArray.push_back(newArr);
	}

	return true;
}

bool MySpriteManager::loadSpriteInfoFile(wstring wszInfoFileName)
{
	if (std::find(m_InfoFileNameArray.begin(), m_InfoFileNameArray.end(), wszInfoFileName) != m_InfoFileNameArray.end())
	{
		return false;
	}

	std::wifstream wiFp;
	std::wstring wszbuf;
	INT type;

	wiFp.open(wszInfoFileName, std::ios::in);
	if (!wiFp) { return false; }

	wiFp >> wszbuf;

	while (true)
	{
		wiFp >> wszbuf;
		if (wszbuf == L"#END") { break; }

		wiFp >> type;

		if (type)
		{
			if (!loadMultiTexSprite(wiFp)) { return false; };
		}
		else
		{
			m_tempRtSpriteName.push_back(wszbuf);
			if (!loadSingleTexSprite(wiFp)) { return false; };
		}
	}
	
	return true;
}

bool MySpriteManager::loadSprites(wstring wszInfoFileName)
{
	m_tempRtArray.clear();
	m_tempTexArray.clear();
	m_tempRtSpriteName.clear();
	m_tempTexSpriteName.clear();

	if (!loadSpriteInfoFile(wszInfoFileName)) { return false; }
	else { m_InfoFileNameArray.push_back(wszInfoFileName); }

	for (int i = 0; i < m_tempRtArray.size(); i++)
	{
		if (m_spriteMap.find(m_tempRtSpriteName[i]) == m_spriteMap.end())
		{
			MySprite* newE = new MySprite;
			newE->m_IDname = m_tempRtSpriteName[i];
			newE->m_rtSpriteArray = m_tempRtArray[i];

			m_spriteMap.insert(std::make_pair(m_tempRtSpriteName[i], newE));
		}
	}

	for (int i = 0; i < m_tempTexArray.size(); i++)
	{
		if (m_spriteMap.find(m_tempTexSpriteName[i]) == m_spriteMap.end())
		{
			MySprite* newE = new MySprite;
			newE->m_IDname = m_tempTexSpriteName[i];
			newE->m_texSpriteArray = m_tempTexArray[i];

			m_spriteMap.insert(std::make_pair(m_tempTexSpriteName[i], newE));
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
	for (map<wstring, MySprite*>::iterator::value_type it : m_spriteMap)
	{
		delete it.second;
		it.second = nullptr;
	}

	m_spriteMap.clear();
	m_InfoFileNameArray.clear();
	m_tempRtArray.clear();
	m_tempTexArray.clear();
	m_tempRtSpriteName.clear();
	m_tempTexSpriteName.clear();

	return true;
}

MySprite* MySpriteManager::getSprite(wstring wszSpriteName)
{
	map<wstring, MySprite*>::iterator it = m_spriteMap.find(wszSpriteName);
	if (it != m_spriteMap.end()) { return it->second; }
	else { return nullptr; }
}