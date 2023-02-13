#include "game_main.h"

#include "../../../common_data/common_data.h"
#include "../../../sound_manager/game_sound_manager.h"
#include "../../../bag/bag_data.h"
#include "loop_game/loop_game.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../money_manager/money_manager.h"
#include "../../../bag/bag.h"

CGameMain::CGameMain(IGameObject* parent)
	:IScene(parent, "GameMain")
	, m_Frame(0.0f)
	, m_Timer(0.0f)
{
}

void CGameMain::Initialize()
{
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::GAME_BGM);
	aqua::CreateGameObject<CBagData>(this);
	aqua::CreateGameObject<CLoopGame>(this);
	aqua::CreateGameObject<CUIManager>(this);
	aqua::CreateGameObject<CMoneyManager>(this);
	aqua::CreateGameObject<CBag>(this);

	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData = m_CommonData->GetData();
	aqua::IGameObject::Initialize();

	m_LoopGame = (CLoopGame*)aqua::FindGameObject("LoopGame");

	// ゲームタイマーセット
	m_GameTimer.Setup(1000.0f);
}

void CGameMain::Update()
{
	// ゲームタイマーの更新
	m_GameTimer.Update();

	//if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	//	((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);

	if(m_LoopGame->ChengeResult())
			((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);

	aqua::IGameObject::Update();
}

void CGameMain::Draw()
{
	aqua::IGameObject::Draw();
}

void CGameMain::Finalize()
{
	m_SoundManager->Stop(SoundID::GAME_BGM);

	aqua::IGameObject::Finalize();
}

float CGameMain::GetGameTime(void)
{
	return m_GameTimer.GetTime();
}