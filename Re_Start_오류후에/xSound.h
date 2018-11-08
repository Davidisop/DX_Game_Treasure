#pragma once
#include "xStd.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod64_vc.lib")
using namespace FMOD;
const int g_iMaxSound = 32;

class dxSound
{
public:
	static dxSound* Get()
	{
		static dxSound sound;
		return &sound;
	}
public:
	FMOD::System*   m_pSystem;
	FMOD::Sound*	m_pSound[g_iMaxSound];
	FMOD::Channel*  m_pChannel[g_iMaxSound];
	int   m_iSoundList;
	TCHAR     m_szBuffer[MAX_PATH];
public:
	bool	Init();
	bool	Frame();
	bool	Release();
	bool	Render();
public:
	int     Load(const char* pLoadName, bool bPlay);
	void    Play(int iIndex, bool bPlay = true, bool bLoop = false);
	void    PlayEffect(int iIndex);
	void    Stop(int iIndex);
	void    paused(int iIndex);
	void    Volume(int iIndex, float fVolume, bool bUp);
public:
	dxSound();
	virtual ~dxSound();
};

#define sSound dxSound::Get()


bool dxSound::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	sSound->Load("../../data/00_Menu.mp3", false);//0
	sSound->Load("../../data/boss_gun.wav", false);

	sSound->Load("../../data/game_background.mp3",false);//2

	sSound->Load("../../data/hero_fire.wav", false);//3
	sSound->Load("../../data/hero_energy.wav", false);
	sSound->Load("../../data/hero_sword.wav", false);
	
	sSound->Load("../../data/ghost.wav", false);//6

	sSound->Load("../../data/boss_gun.wav", false);//7
	sSound->Load("../../data/boss_sword.wav", false);
	sSound->Load("../../data/robot_reaction1.wav", false);
	sSound->Load("../../data/robot_reaction2.wav", false);
	sSound->Load("../../data/robot_emrge.wav", false);
	

	sSound->Load("../../data/box_open.wav", false); //12

	sSound->Load("../../data/succes_ending.wav", false); //13
	sSound->Load("../../data/fail_ending.wav", false);

	return true;
}
int    dxSound::Load(const char* pLoadName, bool bPlay)
{
	Channel* pChannel = NULL;
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT,
		0, &m_pSound[m_iSoundList++]);
	if (bPlay == true)
	{
		m_pSystem->playSound(m_pSound[m_iSoundList - 1], 0,
			false, &pChannel);
		m_pChannel[m_iSoundList - 1] = pChannel;
	}

	return m_iSoundList - 1;
};
void     dxSound::PlayEffect(int iIndex)
{
	if (g_bActiveApp == false) return;
	Channel* pChannel = NULL;
	m_pSystem->playSound(m_pSound[iIndex], false,
		false, &pChannel);
	m_pChannel[iIndex] = pChannel;
}
void    dxSound::Play(int iIndex, bool bPlay, bool bLoop)
{
	if (g_bActiveApp == false) return;
	bool playing = false;
	if (m_pChannel[iIndex] != NULL)
	{
		m_pChannel[iIndex]->isPlaying(&playing);
	}
	if (playing == false)
	{
		if (bLoop)
			m_pSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		else
			m_pSound[iIndex]->setMode(FMOD_LOOP_OFF);

		m_pSystem->playSound(m_pSound[iIndex], false,
			false, &m_pChannel[iIndex]);
	}
}
void    dxSound::Stop(int iIndex)
{
	if (g_bActiveApp == false) return;
	m_pChannel[iIndex]->stop();
}
void    dxSound::paused(int iIndex)
{
	if (g_bActiveApp == false) return;
	bool paused;
	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}
void    dxSound::Volume(int iIndex, float fVolume, bool bUp)
{
	if (g_bActiveApp == false) return;
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (bUp == true)
	{
		fCurrentVolume += fVolume;
		fCurrentVolume = min(1.0f, fCurrentVolume);
	}
	else
	{
		fCurrentVolume -= fVolume;
		fCurrentVolume = max(0.0f, fCurrentVolume);
	}
	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}
bool dxSound::Frame()
{
	m_pSystem->update();

	unsigned int total = 0;
	unsigned int ms = 0;
	m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);
	m_pChannel[0]->getPosition(&ms, FMOD_TIMEUNIT_MS);

	return true;
}
bool dxSound::Render()
{
	return true;
}
bool dxSound::Release()
{
	for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
dxSound::dxSound()
{
	m_iSoundList = 0;
}


dxSound::~dxSound()
{
}
