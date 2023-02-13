#pragma once

#include "../../scene_manager.h"

class CResult : public IScene
{
public: // 公開メンバ関数

	// コンストラクタ
	CResult(IGameObject* parent);

	// デストラクタ
	~CResult(void) = default;

	// 初期化関数
	void Initialize(void)	override;

	// 更新関数
	void Update(void)	override;

	// 描画関数
	void Draw(void)	override;

	// 解放関数
	void Finalize(void)	override;

private: // 非公開メンバ関数

	// スコアボードスプライト
	aqua::CSprite m_ScoreBoardSprite;

	// 背景スプライト
	aqua::CSprite m_BackGround;

	// 枠スプライト（１枚目）
	aqua::CSprite m_FrameFirst;

	// 枠スプライト（２枚目）
	aqua::CSprite m_FrameSecond;

	// 銅メダルスプライト
	aqua::CSprite m_MedalSprite;

	// 銀メダルスプライト
	aqua::CSprite m_SilverMedalSprite;

	// 金メダルスプライト
	aqua::CSprite m_GoldMedalSprite;

	// スコアメータースプライト
	aqua::CSprite m_ScoreMeter;

	// イージングタイマー
	aqua::CTimer m_EasingTimer;

private: // 非公開メンバ定数

	static const aqua::CVector2 m_medal_position;

	//////////////////////////////////////////////////////////////
	aqua::CLabel m_ClearTimeText;
	aqua::CLabel m_EasyNumText;
	aqua::CLabel m_NormalNumText;
	aqua::CLabel m_HardText;
	aqua::CLabel m_TotalScoreText;

	float m_ClearTime;


	POINT mouse;
	int X;
	int Y;
};