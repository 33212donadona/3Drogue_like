#pragma once
#include "aqua.h"

class CSelectSystem;

enum class LAVEL_BG
{
	SUB,
	MEDIUM,
	HIGH,

	MAX
};

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

	aqua::CSurface& GetBackGround();

private:

	void ChangeBackGournd();

private:
	static const int   m_max_sky;                                  //! 空画像の最大数
	static const int   m_max_effect;                               //! エフェクトの画像の最大数
	static const float m_sprite_move_speed;                        //! 画像の動作速度
	static const std::string m_filr_name[(int)LAVEL_BG::MAX];
	std::vector<std::vector<aqua::CSprite>>    m_ScrollSkySprite;  //! 空の画像
	aqua::CSprite*     m_EffectSprite;                             //! エフェクトの画像
	float              m_EffectRota;                               //! エフェクトの回転

	CSelectSystem* m_SelectSystem;
	unsigned char  m_AlphaReta;

	aqua::CSurface m_BackGroundSurface;
};