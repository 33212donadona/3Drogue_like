#pragma once
#include "aqua.h"
class CSelectBackGround :
	public aqua::IGameObject
{
public :

	CSelectBackGround(aqua::IGameObject* parent);
	~CSelectBackGround() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

	int GetBackGround();


private:
	static const int m_max_sky;             //! 空画像の最大数
	static const int m_max_effect;          //! エフェクトの画像の最大数
	static const float m_sprite_move_speed; //! 画像の動作速度
	aqua::CSprite* m_ScrollSkySprite;       //! 空の画像
	aqua::CSprite* m_EffectSprite;          //! エフェクトの画像
	float          m_EffectRota;            //! エフェクトの回転

	aqua::CSurface m_BackGroundSurface;
};