#include "loop_game.h"
#include "../../../../stage/stage.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera_manager/game_camera/game_camera.h"
#include "../../../../common_data/common_data.h"
#include "../../../../scene_manager/scene/3_game_main/game_main.h"
#include "../../../../input/input.h"

const float CLoopGame::m_fade_max_time = 2.0f;
const float CLoopGame::m_light_max_time = 0.25f;
const float CLoopGame::m_button_space = 20.0f;
const std::string CLoopGame::m_lever_file_name[] =
{
	"data\\game_graph\\stage_lever_ease.png",
	"data\\game_graph\\stage_lever_nomal.png",
	"data\\game_graph\\stage_lever_hard.png"
};
const std::string CLoopGame::m_lever_light_file_name[] =
{
	"data\\game_graph\\stage_lever_ease_light.png",
	"data\\game_graph\\stage_lever_nomal_light.png",
	"data\\game_graph\\stage_lever_hard_light.png"
};
const std::string CLoopGame::m_button_file_name[] =
{
	"data\\game_graph\\button_x.png",
	"data\\game_graph\\button_b.png"
};

CLoopGame::CLoopGame(IGameObject* parent)
	:aqua::IGameObject(parent, "LoopGame")
	, m_LoopState(LOOP_STATE::FADE_IN)
	, m_LightFlag(false)
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

	// シーン遷移の演出用
	m_FadeBox.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowSize().x, (float)aqua::GetWindowSize().y, aqua::CColor::BLACK);

	// タイマーの初期化
	m_FadeTimer.Setup(m_fade_max_time);
	m_LightTimer.Setup(m_light_max_time);

	// ラベルの初期化
	m_SelectLabel.Create(40);
	m_SelectLabel.text = "次のステージの難易度を選択してください";
	m_SelectLabel.position.x = float(aqua::GetWindowWidth() - m_SelectLabel.GetTextWidth()) / 2.0f;
	m_SelectLabel.position.y = aqua::GetWindowHeight() / 3;

	// 画像の初期化
	for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
	{
		m_LeverSprite[l_i].Create(m_lever_file_name[l_i]);
		m_LeverSpriteLight[l_i].Create(m_lever_light_file_name[l_i]);

		m_LeverSprite[l_i].position = aqua::GetWindowSize() / 2;

		m_LeverSprite[l_i].position.y -= m_LeverSprite[l_i].GetTextureHeight() / 2;
		m_LeverSprite[l_i].position.x -= m_LeverSprite[l_i].GetTextureWidth() / 2;

		m_LeverSprite[l_i].color.alpha = (unsigned char)0;

		m_LeverSpriteLight[l_i].position = m_LeverSprite[l_i].position;
		m_LeverSpriteLight[l_i].color.alpha = m_LeverSprite[l_i].color.alpha;
		m_LeverSpriteLight[l_i].anchor.x = m_LeverSpriteLight[l_i].GetTextureWidth() / 2;
		m_LeverSpriteLight[l_i].anchor.y = m_LeverSpriteLight[l_i].GetTextureHeight() / 2;
	}

	for (int i = 0; i < 2; i++)
		m_NextLever[i] = aqua::Rand((int)STAGE_LEVER::HARD, (int)STAGE_LEVER::EASE);

	if (m_NextLever[0] == m_NextLever[1])
		m_NextLever[1] = (m_NextLever[1] + 1) % (int)STAGE_LEVER::MAX;

	for (int i = 0; i < (int)SELECT_BUTTON::MAX; i++)
	{
		m_ButtonSprite[i].Create(m_button_file_name[i]);

		m_LeverSprite[m_NextLever[i]].color.alpha = (unsigned char)255;

		if (i)
			m_LeverSprite[m_NextLever[i]].position.x += aqua::GetWindowWidth() / 4;
		else
			m_LeverSprite[m_NextLever[i]].position.x -= aqua::GetWindowWidth() / 4;

		m_LeverSpriteLight[m_NextLever[i]].position = m_LeverSprite[m_NextLever[i]].position;

		m_ButtonSprite[i].position = m_LeverSprite[m_NextLever[i]].position;
		m_ButtonSprite[i].position.x -= m_ButtonSprite[i].GetTextureWidth() + m_button_space;
		m_ButtonSprite[i].position.y -= m_ButtonSprite[i].GetTextureHeight() / 4;
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

			m_GameData.game_crea_time += ((CGameMain*)aqua::FindGameObject("GameMain"))->GetGameTime();

			m_CommonData->SetData(m_GameData);

			for (int i = 0; i < 2; i++)
				m_LeverSprite[m_NextLever[i]].color.alpha = (unsigned)255;

			m_LoopState = LOOP_STATE::SELECT_LEVER;

			m_LightTimer.Reset();
			m_FadeTimer.Reset();
		}

		break;

	case LOOP_STATE::SELECT_LEVER:

		SelectNextStageLaver();

		if (m_SelectNextStageFlag)
			m_LightFlag = true;

		if (m_LightFlag)
		{
			int select_num = (int)m_CommonData->GetData().stage_lever;

			m_LeverSprite[select_num].color.alpha = (unsigned)0;

			if (!m_LightTimer.Finished())
			{
				m_LeverSpriteLight[select_num].color.alpha =
					(unsigned char)aqua::easing::InCubic
					(
						m_LightTimer.GetTime(),
						m_LightTimer.GetLimit(),
						0,
						255
					);

				m_LeverSpriteLight[select_num].scale = aqua::CVector2::ONE *
					aqua::easing::InCubic
					(
						m_LightTimer.GetTime(),
						m_LightTimer.GetLimit(),
						1.0f,
						1.5f
					);
			}
			else
			{
				m_LeverSpriteLight[select_num].color.alpha =
					(unsigned char)aqua::easing::InCubic
					(
						m_LightTimer.GetTime() - m_LightTimer.GetLimit(),
						m_LightTimer.GetLimit(),
						255,
						0
					);

				m_LeverSpriteLight[select_num].scale = aqua::CVector2::ONE *
					aqua::easing::InCubic
					(
						m_LightTimer.GetTime() - m_LightTimer.GetLimit(),
						m_LightTimer.GetLimit(),
						1.5f,
						1.0f
					);

				if (m_LeverSpriteLight[select_num].color.alpha == (unsigned char)0)
					m_LightFlag = false;

			}

			m_LightTimer.Update();
		}
		else if (m_LightTimer.Finished() && !m_LightFlag)
		{
			aqua::CreateGameObject<CStage>(this);
			m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
			aqua::CreateGameObject<CGameCamera>(this);

			IGameObject::Initialize();
			m_LoopState = LOOP_STATE::FADE_IN;
		}

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
		{
			m_LeverSprite[l_i].Draw();
			m_LeverSpriteLight[l_i].Draw();
		}

		for (int b_i = 0; b_i < (int)SELECT_BUTTON::MAX; b_i++)
			m_ButtonSprite[b_i].Draw();

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
	{
		m_LeverSprite[l_i].Delete();
		m_LeverSpriteLight[l_i].Delete();
	}
	for (int b_i = 0; b_i < (int)SELECT_BUTTON::MAX; b_i++)
		m_ButtonSprite[b_i].Delete();

	IGameObject::Finalize();
}

bool CLoopGame::ChengeResult()
{
	return m_CommonData->GetData().crea_stage >= m_CommonData->GetData().crea_target;
}

void CLoopGame::SelectNextStageLaver()
{
	CommonDataInfo info = m_CommonData->GetData();

	if (Input::In(Input::BUTTON_ID::X))
		info.stage_lever = (STAGE_LEVER)m_NextLever[0];

	if (Input::In(Input::BUTTON_ID::B))
		info.stage_lever = (STAGE_LEVER)m_NextLever[1];

	m_CommonData->SetData(info);

	m_SelectNextStageFlag = Input::In(Input::BUTTON_ID::B) || Input::In(Input::BUTTON_ID::X);
}
