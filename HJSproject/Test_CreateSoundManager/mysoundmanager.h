#pragma once
#include "myunih.h"

#include "fmod.h"			//C용 헤더
#include "fmod.hpp"			//C++용 헤더
#include "fmod_errors.h"	//디버그와 처리확인을 위한 헤더

#include <io.h>

#pragma comment(lib, "fmod_vc.lib")

using std::map;
using std::wstring;
using std::vector;

class MySound
{
protected:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

public:
	MySound();
	~MySound();

	FMOD_RESULT create(FMOD::System* pSystem, std::string szFilename);

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

class MySoundManager : public Singleton<MySoundManager>
{
	friend class Singleton<MySoundManager>;
private:
	FMOD::System* m_pSystem;
	map<wstring, MySound*> m_soundMap;
	vector<wstring> m_fileList;

	MySoundManager();
	~MySoundManager();

public:
	MySound* loadSound(wstring wszFilename);
	bool loadDir(wstring wszPath);
	wstring& getSplitName(wstring wszFullPath);

	bool init();
	bool frame();
	bool render();
	bool release();
};

#define SOUND_MANAGER MySoundManager::getInstance()
#define LOAD_SOUND(wszFileName) MySoundManager::getInstance().loadSound(wszFileName);