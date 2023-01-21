#include "game_sound_manager.h"

const SoundInfo CGameSoundManager::m_Sound[(int)SoundID::MAX] =
{
	{"data\\bgm\\title.mp3",true},
	{"data\\bgm\\select.mp3",true},
	{"data\\bgm\\game_main.mp3",true},
	{"data\\bgm\\result.mp3",true}
};

CGameSoundManager::CGameSoundManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "GameSoundManager")
	, m_Finalize(false)
{
}

void CGameSoundManager::Initialize()
{
	for (int s_i = 0; s_i < (int)SoundID::MAX; s_i++)
		m_SoundList[s_i].Create(m_Sound[s_i].name, m_Sound[s_i].flag);
}

void CGameSoundManager::Finalize()
{
	for (auto& i : m_SoundList)
		i.Delete();
	m_Finalize = true;
	IGameObject::Finalize();
}

void CGameSoundManager::Play(SoundID id)
{
	int sound_id = (int)id;
	
	if (!m_SoundList[sound_id].IsPlaying() && m_Sound[sound_id].flag)
		m_SoundList[sound_id].Play();

	if (!m_Sound[sound_id].flag)
		m_SoundList[sound_id].Play();
}

void CGameSoundManager::Stop(SoundID id)
{
	if (!m_Finalize && m_SoundList[(int)id].IsPlaying())
	{
		m_SoundList[(int)id].ReStart();
		m_SoundList[(int)id].Stop();
	}
}
