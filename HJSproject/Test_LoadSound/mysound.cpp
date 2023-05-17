#include "mysound.h"

MySounder::MySounder()
{
	m_pSystem = nullptr;
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

MySounder::~MySounder()
{
	release();
}

FMOD_RESULT MySounder::create()
{
	FMOD_RESULT fr = FMOD_OK;

	fr = FMOD::System_Create(&m_pSystem);

	return fr;
}

FMOD_RESULT MySounder::loadSound(std::string szFilename)
{
	FMOD_RESULT fr = FMOD_OK;

	fr = m_pSystem->createSound(szFilename.c_str(), FMOD_DEFAULT,
		nullptr, &m_pSound);

	return fr;
}

FMOD_RESULT MySounder::play(bool loopFlag)
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

FMOD_RESULT MySounder::playEffect(bool loopFlag)
{
	FMOD_RESULT fr = FMOD_OK;

	fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	if (fr) { return fr; }

	fr = setLoop(loopFlag);

	return fr;
}

FMOD_RESULT MySounder::setLoop(bool loopFlag)
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel)
	{
		if (loopFlag) { fr = m_pChannel->setMode(FMOD_LOOP_NORMAL); }
		else { fr = m_pChannel->setMode(FMOD_LOOP_OFF); }
	}

	return fr;
}

FMOD_RESULT MySounder::stop()
{
	FMOD_RESULT fr = FMOD_ERR_CHANNEL_ALLOC;

	if (m_pChannel) { fr = m_pChannel->stop(); }

	return fr;
}

FMOD_RESULT MySounder::togglePause()
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

FMOD_RESULT MySounder::volumeUp(UINT scale)
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

FMOD_RESULT MySounder::volumeDown(UINT scale)
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

UINT MySounder::getSoundLengthMs()
{
	UINT len = -1;
	if (m_pSound) { m_pSound->getLength(&len, FMOD_TIMEUNIT_MS); }

	return len;
}

UINT MySounder::getCurSoundPosMs()
{
	UINT cPos = -1;
	if(m_pChannel) { m_pChannel->getPosition(&cPos, FMOD_TIMEUNIT_MS); }

	return cPos;
}

bool MySounder::init()
{
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	return true;
}

bool MySounder::frame()
{
	//시스템 인터페이스를 소유하고 있는 객체에서 매 프레임마다 갱신해 주어야 함 
	m_pSystem->update();
	return true;
}

bool MySounder::render()
{
	return true;
}

bool MySounder::release()
{
	if (m_pSound) { m_pSound->release(); m_pSound = nullptr; }
	if (m_pSystem) { m_pSystem->close(); m_pSystem->release(); m_pSystem = nullptr; }

	return true;
}
