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
	static const int m_max_sky;             //! ��摜�̍ő吔
	static const int m_max_effect;          //! �G�t�F�N�g�̉摜�̍ő吔
	static const float m_sprite_move_speed; //! �摜�̓��쑬�x
	aqua::CSprite* m_ScrollSkySprite;       //! ��̉摜
	aqua::CSprite* m_EffectSprite;          //! �G�t�F�N�g�̉摜
	float          m_EffectRota;            //! �G�t�F�N�g�̉�]

	aqua::CSurface m_BackGroundSurface;
};