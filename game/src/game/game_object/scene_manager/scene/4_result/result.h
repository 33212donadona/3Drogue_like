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

	// 背景スプライト（１枚目）
	aqua::CSprite m_BackGroundFirst;

	// 背景スプライト（２枚目）
	aqua::CSprite m_BackGroundSecond;

	aqua::CLabel m_Label;

	// ゲームクリア時間
	float m_ClearTime;
};