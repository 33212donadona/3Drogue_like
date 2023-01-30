#include "result.h"

#include "../../../sound_manager/game_sound_manager.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{
	m_ScoreBoardSprite.Create("data/score_board.png");
	m_BackGroundFirst.Create("data/result_bg.png");
	m_BackGroundSecond.Create("data/result_bg.png");

	m_BackGroundSecond.position.x = aqua::GetWindowWidth();
}

void CResult::Update(void)
{
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
	m_BackGroundSecond.Draw();
	m_BackGroundFirst.Draw();
	m_ScoreBoardSprite.Draw();

	IScene::Draw();
}

void CResult::Finalize(void)
{
	m_BackGroundSecond.Delete();
	m_BackGroundFirst.Delete();
	m_ScoreBoardSprite.Delete();
}
