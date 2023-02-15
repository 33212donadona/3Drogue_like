#include "select.h"
#include "../../../select_back_ground/select_back_ground.h"
#include "../../../camera_manager/select_camera/select_camera.h"
#include "select_system/select_system.h"
#include "../../../sound_manager/game_sound_manager.h"

CSelect::CSelect(IGameObject* parent)
	:IScene(parent,"Select")
{
}

void CSelect::Initialize()
{
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::SELECT);
	aqua::CreateGameObject<CSelectBackGround>(this);
	aqua::CreateGameObject<CSelectSystem>(this);
	aqua::CreateGameObject<CSelsectCamera>(this);

	m_SelectBottonSprite.Create("data\\select_graph\\決定ボタン.png");
	m_SelectBottonSprite.position = aqua::GetWindowSize();
	m_SelectBottonSprite.position.x -= m_SelectBottonSprite.GetTextureWidth();
	m_SelectBottonSprite.position.y -= m_SelectBottonSprite.GetTextureHeight();

	aqua::IGameObject::Initialize();
}

void CSelect::Update()
{
	// スペースでゲームシーンへ移動
	if (((CSelectSystem*)aqua::FindGameObject("SelectSystem"))->GetDecisionSelsectLavel())
	{
		m_SoundManager->Play(SoundID::SENE_BOTTON);
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::GAMEMAIN);
	}

	aqua::IGameObject::Update();
}

void CSelect::Draw()
{
	aqua::IGameObject::Draw();
	m_SelectBottonSprite.Draw();
}

void CSelect::Finalize()
{
	m_SoundManager->Stop(SoundID::SELECT);
	aqua::IGameObject::Finalize();
	m_SelectBottonSprite.Delete();
}
