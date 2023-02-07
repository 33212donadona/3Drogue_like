#include "game_main.h"
#include "loop_game/loop_game.h"

#include "../../../common_data/common_data.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../stage/stage.h"
#include "../../../camera_manager/game_camera/game_camera.h"
#include "../../../money_manager/money_manager.h"
#include "../../../bag/bag.h"
#include "../../../bag/bag_data.h"
#include "../../../sound_manager/game_sound_manager.h"

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
	//aqua::CreateGameObject<CStage>(this);
	//m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
	//aqua::CreateGameObject<CGameCamera>(this);

	m_LoopGame = aqua::CreateGameObject<CLoopGame>(this);
	aqua::CreateGameObject<CMoneyManager>(this);
	aqua::CreateGameObject<CBag>(this);

	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData = m_CommonData->GetData();
	aqua::IGameObject::Initialize();

	// ゲームタイマーセット
	m_GameTimer.Setup(1000.0f);
}

void CGameMain::Update()
{
	// ゲームタイマーの更新
	m_GameTimer.Update();

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);

	//if (m_UnitManager->EmptyEnemyList())
	//{
	//	m_GameData.crea_stage++;
	//
	//	if (m_GameData.crea_stage == m_CommonData->GetData().crea_target)
	//	{
	//		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);
	//		m_GameData.game_crea_time += m_Timer;
	//	}
	//	else
	//	{
	//		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::GAMEMAIN);
	//	}
	//	m_CommonData->SetData(m_GameData);
	//}

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
