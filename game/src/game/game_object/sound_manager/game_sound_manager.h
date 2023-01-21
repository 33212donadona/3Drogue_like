#pragma once
#include "aqua.h"

#include "game_sound_id.h"
class CGameSoundManager :
	public aqua::IGameObject
{
public:
	CGameSoundManager(aqua::IGameObject* parent);
	~CGameSoundManager() = default;

	void Initialize()override;
	void Finalize()override;

	void Play(SoundID id);
	void Stop(SoundID id);
private:

	aqua::CSoundPlayer m_SoundList[(int)SoundID::MAX];
	bool m_Finalize;
	static const SoundInfo m_Sound[(int)SoundID::MAX];

};

