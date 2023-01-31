#include "result.h"

#include "../../../sound_manager/game_sound_manager.h"
#include "../../../common_data/common_data.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{
	m_ScoreBoardSprite.Create("data/score_board.png");
	m_ScoreBoardSprite.position.x = -1000;

	m_BackGround.Create("data/abeb.png");

	m_BackGroundFirst.Create("data/abea.png");
	m_BackGroundSecond.Create("data/abea.png");

	m_BackGroundSecond.position.x = aqua::GetWindowWidth();

	m_Label.Create(50);
	m_Label.position.x = 600;
	m_Label.position.y = 290;
	m_Label.color.alpha = 0;

	m_ClearTime = ((CCommonData*)aqua::FindGameObject("CommonData"))->GetData().game_crea_time;

	m_Label.text = std::to_string(m_ClearTime);

	m_EasingTimer.Setup(0.5f);
}

void CResult::Update(void)
{
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}
	else
	{
		m_Label.color.alpha+=5;
	}

	m_ScoreBoardSprite.position.x = aqua::easing::InCubic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(),-1000, 0);

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);

	m_BackGroundFirst.position.x--;
	m_BackGroundSecond.position.x--;

	if (m_BackGroundFirst.position.x < -1919)
		m_BackGroundFirst.position.x = 1920;

	if (m_BackGroundSecond.position.x < -1919)
		m_BackGroundSecond.position.x = 1920;
}

void CResult::Draw(void)
{
	m_BackGround.Draw();
	m_BackGroundFirst.Draw();
	m_BackGroundSecond.Draw();
	m_ScoreBoardSprite.Draw();

	m_Label.Draw();
	IScene::Draw();
}

void CResult::Finalize(void)
{
	m_BackGroundSecond.Delete();
	m_BackGroundFirst.Delete();
	m_ScoreBoardSprite.Delete();
}
