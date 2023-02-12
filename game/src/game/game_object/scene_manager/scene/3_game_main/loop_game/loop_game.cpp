#include "loop_game.h"
#include "../../../../stage/stage.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../camera_manager/game_camera/game_camera.h"
#include "../../../../common_data/common_data.h"
#include "../../../../scene_manager/scene/3_game_main/game_main.h"
#include "../../../../input/input.h"
#include "../../../../sound_manager/game_sound_manager.h"

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
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");

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
	m_MaxLightTimer.Setup(m_light_max_time * 2.0f);

	// ラベルの初期化
	m_SelectLeverLabel.Create(40);
	m_SelectLeverLabel.text = "【次のステージの難易度を選択してください】";
	m_SelectLeverLabel.position.x = float(aqua::GetWindowWidth() - m_SelectLeverLabel.GetTextWidth()) / 2.0f;
	m_SelectLeverLabel.position.y = (float)aqua::GetWindowHeight() / 3;

	m_SelectJobLabel.Create(40);
	m_SelectJobLabel.text = "【どの職に就きますか？】";
	m_SelectJobLabel.position.x = float(aqua::GetWindowWidth() - m_SelectJobLabel.GetTextWidth()) / 2.0f;
	m_SelectJobLabel.position.y = (float)aqua::GetWindowHeight() / 3;

	m_SelectJobSubLabel.Create(35);
	m_SelectJobLabel.text = "【変更したくない場合は現在の職を押してください】";
	m_SelectJobLabel.position.x = float(aqua::GetWindowWidth() - m_SelectJobLabel.GetTextWidth()) / 2.0f;
	m_SelectJobLabel.position.y = (float)aqua::GetWindowHeight() / 3 + m_SelectJobLabel.GetFontHeight();

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
		m_LeverSpriteLight[l_i].anchor.x = (float)m_LeverSpriteLight[l_i].GetTextureWidth() / 2;
		m_LeverSpriteLight[l_i].anchor.y = (float)m_LeverSpriteLight[l_i].GetTextureHeight() / 2;
	}

	for (int i = 0; i < (int)SELECT_BUTTON_SIDE::MAX; i++)
		m_NextLever[i] = aqua::Rand((int)STAGE_LEVER::HARD, (int)STAGE_LEVER::EASE);

	if (m_NextLever[0] == m_NextLever[1])
		m_NextLever[1] = (m_NextLever[1] + 1) % (int)STAGE_LEVER::MAX;

	for (int i = 0; i < (int)SELECT_BUTTON_SIDE::MAX; i++)
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

	if (Input::In(Input::BUTTON_ID::X) && m_UnitManager)
		m_UnitManager->SetPlayerJob(JOB_ID::STUDENT);

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

		if (m_GameData.crea_stage <= m_CommonData->GetData().crea_target)
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

			if (m_GameData.stage_lever == STAGE_LEVER::EASE)
				m_GameData.easy++;
			else if (m_GameData.stage_lever == STAGE_LEVER::NOMAL)
				m_GameData.nomal++;
			else if (m_GameData.stage_lever == STAGE_LEVER::HARD)
				m_GameData.hard++;

			m_CommonData->SetData(m_GameData);

			for (int i = 0; i < 2; i++)
				m_LeverSprite[m_NextLever[i]].color.alpha = (unsigned)255;

			if (m_GameData.crea_stage < m_CommonData->GetData().crea_target)
				m_LoopState = LOOP_STATE::SELECT_LEVER;

			for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
			{
				m_LeverSprite[l_i].position = aqua::GetWindowSize() / 2;

				m_LeverSprite[l_i].position.y -= m_LeverSprite[l_i].GetTextureHeight() / 2;
				m_LeverSprite[l_i].position.x -= m_LeverSprite[l_i].GetTextureWidth() / 2;

				m_LeverSprite[l_i].color.alpha = (unsigned char)0;

				m_LeverSpriteLight[l_i].position = m_LeverSprite[l_i].position;
				m_LeverSpriteLight[l_i].color.alpha = m_LeverSprite[l_i].color.alpha;
			}

			for (int i = 0; i < (int)SELECT_BUTTON_SIDE::MAX; i++)
				m_NextLever[i] = aqua::Rand((int)STAGE_LEVER::HARD, (int)STAGE_LEVER::EASE);

			if (m_NextLever[0] == m_NextLever[1])
				m_NextLever[1] = (m_NextLever[1] + 1) % (int)STAGE_LEVER::MAX;

			for (int i = 0; i < (int)SELECT_BUTTON_SIDE::MAX; i++)
			{
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

			m_FadeTimer.Reset();
		}

		break;

	case LOOP_STATE::SELECT_LEVER:

		SelectLever();

		break;

	case LOOP_STATE::SELECT_JOB:

		SelectJob();

		break;
	}
}

void CLoopGame::Draw()
{

	IGameObject::Draw();

	m_FadeBox.Draw();

	if (m_LoopState == LOOP_STATE::SELECT_LEVER)
	{
		m_SelectLeverLabel.Draw();

		for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
		{
			m_LeverSprite[l_i].Draw();
			m_LeverSpriteLight[l_i].Draw();
		}

		for (int b_i = 0; b_i < (int)SELECT_BUTTON_SIDE::MAX; b_i++)
			m_ButtonSprite[b_i].Draw();

	}

	if (m_LoopState == LOOP_STATE::SELECT_JOB)
	{
		m_SelectJobLabel.Draw();
		m_SelectJobSubLabel.Draw();
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

	m_SelectLeverLabel.Delete();
	m_SelectJobLabel.Delete();
	m_SelectJobSubLabel.Delete();
	
	for (int l_i = 0; l_i < (int)STAGE_LEVER::MAX; l_i++)
	{
		m_LeverSprite[l_i].Delete();
		m_LeverSpriteLight[l_i].Delete();
	}

	for (int b_i = 0; b_i < (int)SELECT_BUTTON_SIDE::MAX; b_i++)
		m_ButtonSprite[b_i].Delete();

	IGameObject::Finalize();
}

bool CLoopGame::ChengeResult()
{
	if (!m_UnitManager)return m_CommonData->GetData().crea_stage >= m_CommonData->GetData().crea_target;
	return m_CommonData->GetData().crea_stage >= m_CommonData->GetData().crea_target || m_UnitManager->GetPlayerDead();
}

void CLoopGame::SelectNextStageLever()
{
	CommonDataInfo info = m_CommonData->GetData();

	if (Input::In(Input::BUTTON_ID::X))
		info.stage_lever = (STAGE_LEVER)m_NextLever[0];

	if (Input::In(Input::BUTTON_ID::B))
		info.stage_lever = (STAGE_LEVER)m_NextLever[1];

	m_CommonData->SetData(info);

	m_SelectNextStageFlag = Input::In(Input::BUTTON_ID::B) || Input::In(Input::BUTTON_ID::X);
}

void CLoopGame::SelectLever()
{
	SelectNextStageLever();

	if (m_SelectNextStageFlag)
	{
		m_LightFlag = true;
		m_SoundManager->Play(SoundID::STAGE_BOTTON);
	}

	if (m_LightFlag)
	{
		int select_num = (int)m_CommonData->GetData().stage_lever;

		if (m_LightTimer.GetTime() >= m_LightTimer.GetLimit() * 2.0f)
			m_LightTimer.SetTime(m_LightTimer.GetLimit() * 2.0f);

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
				(unsigned char)aqua::easing::OutCubic
				(
					m_LightTimer.GetTime() - m_LightTimer.GetLimit(),
					m_LightTimer.GetLimit(),
					255,
					0
				);

			m_LeverSpriteLight[select_num].scale = aqua::CVector2::ONE *
				aqua::easing::OutCubic
				(
					m_LightTimer.GetTime() - m_LightTimer.GetLimit(),
					m_LightTimer.GetLimit(),
					1.5f,
					1.0f
				);

			if (m_LeverSpriteLight[select_num].scale == aqua::CVector2::ONE)
				m_LightFlag = false;

			if (m_MaxLightTimer.Finished())
				m_LeverSpriteLight[select_num].scale = aqua::CVector2::ONE;
		}

		if (m_MaxLightTimer.Finished())
			m_LightFlag = false;

		m_MaxLightTimer.Update();
		m_LightTimer.Update();
	}
	else if (m_MaxLightTimer.Finished() && !m_LightFlag)
	{
		m_MaxLightTimer.Reset();
		m_LightTimer.Reset();

		aqua::CreateGameObject<CStage>(this);
		m_UnitManager = aqua::CreateGameObject<CUnitManager>(this);
		aqua::CreateGameObject<CGameCamera>(this);

		IGameObject::Initialize();
		m_LoopState = LOOP_STATE::FADE_IN;
	}
}

void CLoopGame::SelectJob()
{
}
