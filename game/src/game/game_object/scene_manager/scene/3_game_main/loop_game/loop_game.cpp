#include "loop_game.h"
#include "../../../../stage/stage.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera_manager/game_camera/game_camera.h"
#include "../../../../common_data/common_data.h"
#include "../../../../scene_manager/scene/3_game_main/game_main.h"
#include "../../../../input/input.h"

const float CLoopGame::m_fade_max_time = 2.0f;

CLoopGame::CLoopGame(IGameObject* parent)
	:aqua::IGameObject(parent, "LoopGame")
	, m_LoopState(LOOP_STATE::FADE_IN)
{
}

void CLoopGame::Initialize()
{
	aqua::CreateGameObject<CStage>(this);
	m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
	aqua::CreateGameObject<CGameCamera>(this);
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData = m_CommonData->GetData();

	m_FadeBox.Setup(aqua::CVector2::ZERO, aqua::GetWindowSize().x, aqua::GetWindowSize().y, aqua::CColor::BLACK);

	m_FadeTimer.Setup(m_fade_max_time);

	IGameObject::Initialize();
}

void CLoopGame::Update()
{
	switch (m_LoopState)
	{
	case LOOP_STATE::FADE_IN:

		if (!m_FadeTimer.Finished())
		{
			m_FadeTimer.Update();

			m_FadeBox.color.alpha = (unsigned char)aqua::easing::InBack(
				m_FadeTimer.GetTime()
				, m_FadeTimer.GetLimit()
				, 255
				, 0
			);
		}
		else
		{
			m_LoopState = LOOP_STATE::UPDATA;

			m_FadeTimer.Reset();
		}
		break;
	case LOOP_STATE::UPDATA:

		if (m_UnitManager->EmptyEnemyList())
		{
			m_FadeTimer.Update();

			m_FadeBox.color.alpha = (unsigned char)aqua::easing::InBack(
				m_FadeTimer.GetTime()
				, m_FadeTimer.GetLimit()
				, 0
				, 255
			);

			if (m_FadeTimer.Finished())
				m_LoopState = LOOP_STATE::FADE_OUT;
		}
		else
			IGameObject::Update();

		break;
	case LOOP_STATE::FADE_OUT:

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

			m_CommonData->SetData(m_GameData);

			m_LoopState = LOOP_STATE::FADE_IN;

			m_FadeTimer.Reset();
		}

		break;
	}
}

void CLoopGame::Draw()
{
	IGameObject::Draw();
	m_FadeBox.Draw();
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

void CLoopGame::SelectNextStageLaver()
{
	CommonDataInfo info = m_CommonData->GetData();

	if (Input::In(Input::BUTTON_ID::B))
		info.stage_lever = STAGE_LEVER::EASE;
	if (Input::In(Input::BUTTON_ID::A))
		info.stage_lever = STAGE_LEVER::NOMAL;
	if (Input::In(Input::BUTTON_ID::X))
		info.stage_lever = STAGE_LEVER::HARD;

	m_SelectNextStageFlag = Input::In(Input::BUTTON_ID::B) || Input::In(Input::BUTTON_ID::A) || Input::In(Input::BUTTON_ID::X);
}
