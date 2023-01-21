#include "game_main.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../stage/stage.h"
#include "../../../money_manager/money_manager.h"
#include "../../../bag/bag.h"
#include "../../../bag/bag_data.h"
#include "../../../game_camera\game_camera.h"
#include "../../../sound_manager/game_sound_manager.h"

CGameMain::CGameMain(IGameObject* parent)
	:IScene(parent,"GameMain")
{
}

void CGameMain::Initialize()
{
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::GAME_BGM);
	aqua::CreateGameObject<CBagData>(this);
	aqua::CreateGameObject<CMoneyManager>(this);
	aqua::CreateGameObject<CStage>(this);
	aqua::CreateGameObject<CUnitManager>(this);
	aqua::CreateGameObject<CGameCamera>(this);
	aqua::CreateGameObject<CBag>(this);

	aqua::IGameObject::Initialize();
}

void CGameMain::Update()
{
	if(aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::GAMEMAIN);

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
