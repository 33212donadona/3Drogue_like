#include "result.h"
#include "../../../sound_manager/game_sound_manager.h"
#include "../../../input/input.h"
#include "../../../common_data/common_data.h"

const aqua::CVector2 CResult::m_medal_position = { 1000,100 };

CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{

	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::RESULT_BGM);

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

	// 銅メダルスプライト生成
	m_BronzeMedalSprite.Create("data/result/bronze_medal.png");
	m_BronzeMedalSprite.position = { 1290,120 };
	m_BronzeMedalSprite.scale = { 0.7f,0.7f };
	// 銀メダルスプライトの生成
	m_SilverMedalSprite.Create("data/result/silver_medal.png");

	// 金メダルスプライトの生成
	m_GoldMedalSprite.Create("data/result/gold_medal.png");

	// スコアメータースプライトの生成
	m_ScoreMeter.Create("data/result/meter_rank.png");
	m_ScoreMeter.position = { 1220,700 };

	// イージングタイマーの設定
	m_EasingTimer.Setup(0.5f);

	// コモンデータポインタを取得
	CCommonData* cd = ((CCommonData*)aqua::FindGameObject("CommonData"));

	// テキスト設定
	m_ClearTimeText.Create(50);
	m_ClearTimeText.position = { 600,290 };
	m_ClearTimeText.text = std::to_string(cd->GetData().game_crea_time);

	m_EasyNumText.Create(50);
	m_EasyNumText.position = { 450,460 };
	m_EasyNumText.text = "500  × " + std::to_string(cd->GetData().easy) + " = " + std::to_string(cd->GetData().easy * 500);

	m_NormalNumText.Create(50);
	m_NormalNumText.position = { 450,620 };
	m_NormalNumText.text = "1000 × " + std::to_string(cd->GetData().nomal) + " = " + std::to_string(cd->GetData().nomal * 1000);

	m_HardText.Create(50);
	m_HardText.position = { 450,780 };
	m_HardText.text = "1500 × " + std::to_string(cd->GetData().hard) + " = " + std::to_string(cd->GetData().hard * 1500);

	int time_score = cd->GetData().game_crea_time;

	//if(time_score<)

	m_TotalScoreText.Create(50);
	m_TotalScoreText.position = { 450,880 };
	m_TotalScoreText.text = std::to_string(cd->GetData().easy * 500 + cd->GetData().nomal * 1000 + cd->GetData().hard * 1500);
}

void CResult::Update(void)
{
	//GetMousePoint(&X, &Y);
	//m_ClearTimeText.text = std::to_string(X) + "/" + std::to_string(Y);

	// 「スペース」キーを押すとタイトルシーンへ遷移する
	if (Input::In(Input::BUTTON_ID::B))
	{
		m_SoundManager->Play(SoundID::SENE_BOTTON);
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);
	}

	// タイマーが終了していなければ、タイマーを更新し続ける
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
	else m_EasingTimer.SetTime(m_EasingTimer.GetLimit());

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
	m_BronzeMedalSprite.Draw();
	m_ScoreMeter.Draw();
	m_ClearTimeText.Draw();
	m_EasyNumText.Draw();
	m_NormalNumText.Draw();
	m_HardText.Draw();
	m_TotalScoreText.Draw();
}

void CResult::Finalize(void)
{
	m_ScoreBoardSprite.Delete();
	m_FrameSecond.Delete();
	m_FrameFirst.Delete();
	m_BackGround.Delete();
	m_BronzeMedalSprite.Delete();
	m_SilverMedalSprite.Delete();
	m_GoldMedalSprite.Delete();
	m_ScoreMeter.Delete();
}
