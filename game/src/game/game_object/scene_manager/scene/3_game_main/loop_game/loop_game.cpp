#include "loop_game.h"
#include "../../../../stage/stage.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera_manager/game_camera/game_camera.h"
#include "../../../../common_data/common_data.h"
#include "../../../../scene_manager/scene/3_game_main/game_main.h"

CLoopGame::CLoopGame(IGameObject* parent)
	:aqua::IGameObject(parent, "LoopGame")
{
}

void CLoopGame::Initialize()
{
	aqua::CreateGameObject<CStage>(this);
	m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
	aqua::CreateGameObject<CGameCamera>(this);
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData = m_CommonData->GetData();
	IGameObject::Initialize();
}

void CLoopGame::Update()
{
	if (m_UnitManager->EmptyEnemyList())
	{
		m_GameData = m_CommonData->GetData();
		m_GameData.crea_stage++;

		if (m_GameData.crea_stage < m_CommonData->GetData().crea_target)
		{
			if (m_UnitManager)
			{
				// 現在のユニットの解放処理を行う
				m_UnitManager->Finalize();

				// 現在のユニットを削除する（子リストから外す）
				m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_UnitManager));

				// ポインタの破棄＆NULL化
				AQUA_SAFE_DELETE(m_UnitManager)
			}

			IGameObject::Finalize();

			aqua::CreateGameObject<CStage>(this);
			m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
			aqua::CreateGameObject<CGameCamera>(this);

			IGameObject::Initialize();

			m_GameData.game_crea_time += ((CGameMain*)aqua::FindGameObject("GameMain"))->GetGameTime();
		}

		m_CommonData->SetData(m_GameData);
	}
	else
		IGameObject::Update();
}

void CLoopGame::Draw()
{

	IGameObject::Draw();
}

void CLoopGame::Finalize()
{
	if (m_UnitManager)
	{
		// 現在のユニットの解放処理を行う
		m_UnitManager->Finalize();
		// 現在のユニットを削除する（子リストから外す）
		m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_UnitManager));
		// ポインタの破棄＆NULL化
		AQUA_SAFE_DELETE(m_UnitManager)
	}

	IGameObject::Finalize();
}

bool CLoopGame::ChengeResult()
{
	return m_CommonData->GetData().crea_stage >= m_CommonData->GetData().crea_target;
}