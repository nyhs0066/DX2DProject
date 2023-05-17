#include "mysoundmanager.h"

MySound::MySound()
{
	m_pSystem = nullptr;
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

MySound::~MySound()
{
	release();
}

FMOD_RESULT MySound::create(FMOD::System* pSystem, std::string szFilename)
{
	FMOD_RESULT fr = FMOD_ERR_INVALID_PARAM;

	m_pSystem = pSystem;
	if (!m_pSystem) { return fr; }

	fr = m_pSystem->createSound(szFilename.c_str(), FMOD_DEFAULT,
		nullptr, &m_pSound);

	return fr;
}

FMOD_RESULT MySound::play(bool loopFlag)
{
	FMOD_RESULT fr = FMOD_OK;

	if (m_pChannel)
	{
		bool playFlag;
		m_pChannel->isPlaying(&playFlag);

		if (playFlag) { return fr; }
	}
	
	fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	if (fr) { return fr; }

	fr = setLoop(loopFlag);

	return fr;
}

FMOD_RESULT MySound::playEffect(bool loopFlag)
{
	FMOD_RESULT fr = FMOD_OK;

	fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	if (fr) { return fr; }

	fr = setLoop(loopFlag);

	return fr;
}

FMOD_RESULT MySound::setLoop(bool loopFlag)
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel)
	{
		if (loopFlag) { fr = m_pChannel->setMode(FMOD_LOOP_NORMAL); }
		else { fr = m_pChannel->setMode(FMOD_LOOP_OFF); }
	}

	return fr;
}

FMOD_RESULT MySound::stop()
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel) { fr = m_pChannel->stop(); }

	return fr;
}

FMOD_RESULT MySound::togglePause()
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel)
	{
		bool pauseFlag;
		fr = m_pChannel->getPaused(&pauseFlag);
		if (fr) { return fr; }

		fr = m_pChannel->setPaused(!pauseFlag);
	}

	return fr;
}

FMOD_RESULT MySound::volumeUp(UINT scale)
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel)
	{
		FLOAT volume;
		fr = m_pChannel->getVolume(&volume);
		if (fr) { return fr; }

		volume = min(1.0f, volume + (scale / 100.0f));
		fr = m_pChannel->setVolume(volume);
	}

	return fr;
}

FMOD_RESULT MySound::volumeDown(UINT scale)
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel)
	{
		FLOAT volume;
		fr = m_pChannel->getVolume(&volume);
		if (fr) { return fr; }

		volume = max(0.0f, volume - (scale / 100.0f));
		fr = m_pChannel->setVolume(volume);
	}

	return fr;
}

UINT MySound::getSoundLengthMs()
{
	UINT len = -1;
	if (m_pSound) { m_pSound->getLength(&len, FMOD_TIMEUNIT_MS); }

	return len;
}

UINT MySound::getCurSoundPosMs()
{
	UINT cPos = -1;
	if(m_pChannel) { m_pChannel->getPosition(&cPos, FMOD_TIMEUNIT_MS); }

	return cPos;
}

bool MySound::init()
{
	return true;
}

bool MySound::frame()
{
	return true;
}

bool MySound::render()
{
	return true;
}

bool MySound::release()
{
	if (m_pSound) { m_pSound->release(); m_pSound = nullptr; }

	return true;
}

MySoundManager::MySoundManager()
{
	m_pSystem = nullptr;
}

MySoundManager::~MySoundManager()
{
	release();
}

MySound* MySoundManager::loadSound(wstring wszFileName)
{
	MySound* ret = nullptr;

	map<wstring, MySound*>::iterator it = m_soundMap.find(wszFileName);

	if (it == m_soundMap.end())
	{
		ret = new MySound;
		assert(ret);

		if (ret->create(m_pSystem, atl_W2M(wszFileName)))
		{
			ret->release();
			delete ret;
			ret = nullptr;
		}

		m_soundMap.insert(make_pair(wszFileName, ret));
		return ret;
	}
	else { return it->second; }

	return ret;
}

bool MySoundManager::loadDir(wstring wszPath)
{
	//wszPath의 마지막에는 /이 붙는다고 가정한다. 없으면 붙이는 것도 좋을 지도
	wstring dirPath = wszPath + L"*.*";

	intptr_t handle;
	_wfinddata_t fd;	//파일 또는 디렉토리의 속성을 나타내는 구조체

	handle = _wfindfirst(dirPath.c_str(), &fd); //실패시 -1을 반환한다.

	if (handle != -1)
	{
		do
		{
			if ((fd.attrib & _A_SUBDIR) && (fd.name[0] != L'.'))
			{
				loadDir(wszPath + fd.name + L"/");
			}
			else if (fd.name[0] != L'.')
			{
				m_fileList.push_back(wszPath + fd.name);
			}
		} while (!_wfindnext(handle, &fd));
	}

	_findclose(handle);

	return false;
}

wstring& MySoundManager::getSplitName(wstring wszFullPath)
{
	wstring ret;

	wchar_t drive[MAX_PATH] = { 0 };
	wchar_t dir[MAX_PATH] = { 0 };
	wchar_t fileName[MAX_PATH] = { 0 };
	wchar_t extension[MAX_PATH] = { 0 };

	//파일 경로 분해
	_wsplitpath_s(wszFullPath.c_str(), drive, dir, fileName, extension);

	ret = fileName;
	ret += extension;

	return ret;
}

bool MySoundManager::init()
{
	FMOD_RESULT fr = FMOD_OK;

	fr = FMOD::System_Create(&m_pSystem);

	fr = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	if (fr) { return false; }
	return true;
}

bool MySoundManager::frame()
{
	//시스템 인터페이스를 소유하고 있는 객체에서 매 프레임마다 갱신해 주어야 함 
	m_pSystem->update();
	return true;
}

bool MySoundManager::render()
{
	return true;
}

bool MySoundManager::release()
{
	for (map<wstring, MySound*>::iterator::value_type it : m_soundMap)
	{
		it.second->release();
		delete it.second;
		it.second = nullptr;
	}

	//시스템이 해제되기 이전에 반드시 다른 리소스가 먼저 해제되어야 한다.
	if (m_pSystem) { m_pSystem->close(); m_pSystem->release(); m_pSystem = nullptr; }

	m_soundMap.clear();

	return true;
}
