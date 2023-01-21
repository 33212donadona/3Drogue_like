#include "result.h"
#include "../../../sound_manager/game_sound_manager.h"
CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::RESULT_BGM);
}

void CResult::Update(void)
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}
}

void CResult::Draw(void)
{
	IScene::Draw();
}

void CResult::Finalize(void)
{
	m_SoundManager->Stop(SoundID::RESULT_BGM);
}
