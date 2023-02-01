#include "result.h"

#include "../../../sound_manager/game_sound_manager.h"
#include "../../../common_data/common_data.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{
	// スコアボードのスプライト生成
	m_ScoreBoardSprite.Create("data/result/score_board.png");

	// スコアボードの初期位置を設定
	m_ScoreBoardSprite.position.x = -1000;

	// 背景スプライトの生成
	m_BackGround.Create("data/result/bg.png");

	// 枠スプライトの生成（１枚目）
	m_FrameFirst.Create("data/result/frame.png");
	// 枠スプライトの生成（２枚目）
	m_FrameSecond.Create("data/result/frame.png");

	// 背景スプライト（２枚目）を（１枚目）の右に配置
	m_FrameSecond.position.x = (float)aqua::GetWindowWidth();

	// イージングタイマーの設定
	m_EasingTimer.Setup(0.5f);


	/////////////////////////////////////////////////////////////////////////////
	m_Label.Create(50);
	m_Label.position.x = 600;
	m_Label.position.y = 290;
	m_Label.color.alpha = 0;
	m_ClearTime = ((CCommonData*)aqua::FindGameObject("CommonData"))->GetData().game_crea_time;
	m_Label.text = std::to_string(m_ClearTime);
}

void CResult::Update(void)
{
	// 「スペース」キーを押すとタイトルシーンへ遷移する
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);

	// タイマーが終了していなければ、タイマーを更新し続ける
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
	// タイマーが終了している場合、数値を点滅させる
	else m_Label.color.alpha += 5;

	// スコアボードのアニメーション処理
	m_ScoreBoardSprite.position.x = aqua::easing::InCubic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), -1000, 0);

	// 背景を左側へ移動させる処理
	m_FrameFirst.position.x--;
	m_FrameSecond.position.x--;

	// 背景（１枚目）の位置が左側へ移動して見えなくなったら右端へ戻す
	if (m_FrameFirst.position.x <= -(float)aqua::GetWindowWidth())
		m_FrameFirst.position.x = (float)aqua::GetWindowWidth();

	// 背景（２枚目）の位置が左側へ移動して見えなくなったら右端へ戻す
	else if (m_FrameSecond.position.x <= -(float)aqua::GetWindowWidth())
		m_FrameSecond.position.x = (float)aqua::GetWindowWidth();
}

void CResult::Draw(void)
{
	m_BackGround.Draw();
	m_FrameFirst.Draw();
	m_FrameSecond.Draw();
	m_ScoreBoardSprite.Draw();

	m_Label.Draw();
}

void CResult::Finalize(void)
{
	m_ScoreBoardSprite.Delete();
	m_FrameSecond.Delete();
	m_FrameFirst.Delete();
	m_BackGround.Draw();
}
