#pragma once

#include "myunih.h"

#include "fmod.h"			//C�� ���
#include "fmod.hpp"			//C++�� ���
#include "fmod_errors.h"	//����׿� ó��Ȯ���� ���� ���

#pragma comment(lib, "fmod_vc.lib")

class MySounder
{
protected:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

public:
	MySounder();
	~MySounder();

	FMOD_RESULT create();
	FMOD_RESULT loadSound(std::string szFilename);

	FMOD_RESULT play(bool loopFlag = false);
	FMOD_RESULT playEffect(bool loopFlag = false);
	FMOD_RESULT setLoop(bool loopFlag);
	FMOD_RESULT stop();

	FMOD_RESULT togglePause();

	FMOD_RESULT volumeUp(UINT scale = 2);
	FMOD_RESULT volumeDown(UINT scale = 2);

	UINT getSoundLengthMs();
	UINT getCurSoundPosMs();

	bool init();
	bool frame();
	bool render();
	bool release();
};