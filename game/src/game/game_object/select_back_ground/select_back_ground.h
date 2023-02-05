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
	static const int   m_max_sky;                                  //! ��摜�̍ő吔
	static const int   m_max_effect;                               //! �G�t�F�N�g�̉摜�̍ő吔
	static const float m_sprite_move_speed;                        //! �摜�̓��쑬�x
	static const std::string m_filr_name[(int)LAVEL_BG::MAX];
	std::vector<std::vector<aqua::CSprite>>    m_ScrollSkySprite;  //! ��̉摜
	aqua::CSprite*     m_EffectSprite;                             //! �G�t�F�N�g�̉摜
	float              m_EffectRota;                               //! �G�t�F�N�g�̉�]

	CSelectSystem* m_SelectSystem;
	unsigned char  m_AlphaReta;

	aqua::CSurface m_BackGroundSurface;
};