#include "game_main.h"
#include "../../../common_data/common_data.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../stage/stage.h"
#include "../../../money_manager/money_manager.h"
#include "../../../bag/bag.h"
#include "../../../bag/bag_data.h"
#include "../../../camera_manager/game_camera/game_camera.h"
#include "../../../sound_manager/game_sound_manager.h"

CGameMain::CGameMain(IGameObject* parent)
	:IScene(parent, "GameMain")
{
}

void CGameMain::Initialize()
{
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::GAME_BGM);
	aqua::CreateGameObject<CBagData>(this);
	aqua::CreateGameObject<CMoneyManager>(this);
	aqua::CreateGameObject<CStage>(this);
	m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
	aqua::CreateGameObject<CGameCamera>(this);
	aqua::CreateGameObject<CBag>(this);

	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData.max_stage = m_CommonData->GetData().max_stage;
	m_GameData.crea_stage = m_CommonData->GetData().crea_stage;
	aqua::IGameObject::Initialize();
}

void CGameMain::Update()
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);

	if (m_UnitManager->EmptyEnemyList())
	{
		m_GameData.crea_stage++;

		if (m_GameData.crea_stage == m_CommonData->GetData().max_stage)
			((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);
		else
			((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::GAMEMAIN);

		m_CommonData->SetData(m_GameData);
	}
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
