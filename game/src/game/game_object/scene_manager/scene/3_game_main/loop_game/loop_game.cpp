#include "loop_game.h"
#include "../../../../stage/stage.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera_manager/game_camera/game_camera.h"
#include "../../../../common_data/common_data.h"
#include "../../../../scene_manager/scene/3_game_main/game_main.h"
#include "../../../../input/input.h"

const float CLoopGame::m_fade_max_time = 2.0f;
const std::string CLoopGame::m_lever_file_name[] =
{
	"data\\game_graph\\stage_lever_ease.png",
	"data\\game_graph\\stage_lever_nomal.png",
	"data\\game_graph\\stage_lever_hard.png"
};

CLoopGame::CLoopGame(IGameObject* parent)
	:aqua::IGameObject(parent, "LoopGame")
	, m_LoopState(LOOP_STATE::FADE_IN)
{
	for (int i = 0; i < 2; i++)
		m_NextLever[i] = 0;
}

void CLoopGame::Initialize()
{
	aqua::CreateGameObject<CStage>(this);
	m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
	aqua::CreateGameObject<CGameCamera>(this);
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_GameData = m_CommonData->GetData();

	m_LeverSprite = AQUA_NEW aqua::CSprite[(int)STAGE_LEVER::MAX];

	m_FadeBox.Setup(aqua::CVector2::ZERO, aqua::GetWindowSize().x, aqua::GetWindowSize().y, aqua::CColor::BLACK);
	m_FadeTimer.Setup(m_fade_max_time);

	m_SelectLabel.Create(40);

	m_SelectLabel.text = "次のステージの難易度を選択してください";

	m_SelectLabel.position.x = (aqua::GetWindowWidth() - m_SelectLabel.GetTextWidth()) / 2;

	m_SelectLabel.position.y -= 100.0f;

	for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
	{
		m_LeverSprite[l_i].Create(m_lever_file_name[l_i]);


		m_LeverSprite[l_i].position = aqua::GetWindowSize() / 2;

		m_LeverSprite[l_i].position.y -= m_LeverSprite[l_i].GetTextureHeight() / 2;
		m_LeverSprite[l_i].position.x -= m_LeverSprite[l_i].GetTextureWidth() / 2;

		m_LeverSprite[l_i].color.alpha = (unsigned char)0;

	}

	for (int i = 0; i < 2; i++)
		m_NextLever[i] = aqua::Rand((int)STAGE_LEVER::HARD, (int)STAGE_LEVER::EASE);

	if (m_NextLever[0] == m_NextLever[1])
		m_NextLever[1] = (m_NextLever[1] + 1) % (int)STAGE_LEVER::MAX;

	for (int i = 0; i < 2; i++)
	{
		m_LeverSprite[m_NextLever[i]].color.alpha = (unsigned char)255;

		if (i)
			m_LeverSprite[m_NextLever[i]].position.x += aqua::GetWindowWidth() / 4;
		else
			m_LeverSprite[m_NextLever[i]].position.x -= aqua::GetWindowWidth() / 4;
	}

	IGameObject::Initialize();
}

void CLoopGame::Update()
{
	switch (m_LoopState)
	{
	case LOOP_STATE::FADE_IN:

		if (!m_FadeTimer.Finished())
		{
			m_FadeBox.color.alpha = (unsigned char)aqua::easing::InCubic(
				m_FadeTimer.GetTime()
				, m_FadeTimer.GetLimit()
				, 255
				, 0
			);

			m_FadeTimer.Update();
		}
		else
		{
			m_FadeBox.color.alpha = (unsigned char)0;

			m_LoopState = LOOP_STATE::UPDATA;

			m_FadeTimer.Reset();
		}
		break;
	case LOOP_STATE::UPDATA:

		if (m_UnitManager->EmptyEnemyList())
		{

			m_FadeBox.color.alpha = (unsigned char)aqua::easing::InCubic(
				m_FadeTimer.GetTime()
				, m_FadeTimer.GetLimit()
				, 0
				, 255
			);

			m_FadeTimer.Update();
		}
		else
			IGameObject::Update();

		if (m_FadeTimer.Finished())
			m_LoopState = LOOP_STATE::FADE_OUT;

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

			m_LoopState = LOOP_STATE::SELECT_LEVER;

			m_FadeTimer.Reset();
		}

		break;

	case LOOP_STATE::SELECT_LEVER:

		SelectNextStageLaver();

		if (m_SelectNextStageFlag)
			m_LoopState = LOOP_STATE::FADE_IN;

		break;
	}
}

void CLoopGame::Draw()
{
	IGameObject::Draw();

	m_FadeBox.Draw();

	if (m_LoopState == LOOP_STATE::SELECT_LEVER)
	{
		m_SelectLabel.Draw();

		for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
			m_LeverSprite[l_i].Draw();
	}

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
	m_SelectLabel.Delete();
	for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
		m_LeverSprite[l_i].Delete();

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
		info.stage_lever = (STAGE_LEVER)m_NextLever[0];
	
	if (Input::In(Input::BUTTON_ID::X))
		info.stage_lever = (STAGE_LEVER)m_NextLever[1];

	m_SelectNextStageFlag = Input::In(Input::BUTTON_ID::B) || Input::In(Input::BUTTON_ID::A) || Input::In(Input::BUTTON_ID::X);
}
