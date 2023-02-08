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

enum class CAN_MOVE_ID
{
	LEFT,
	RIGHT,

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

	void EmittingLight();

private:
	static const int   m_max_sky;                                  //! ��摜�̍ő吔
	static const int   m_max_effect;                               //! �G�t�F�N�g�̉摜�̍ő吔
	static const float m_sprite_move_speed;                        //! �摜�̓��쑬�x
	static const std::string m_bg_filr_name[(int)LAVEL_BG::MAX];
	static const std::string m_light_filr_name[(int)CAN_MOVE_ID::MAX];
	std::vector<std::vector<aqua::CSprite>>    m_ScrollSkySprite;  //! ��̉摜
	
	aqua::CSprite*     m_EffectSprite;                             //! �G�t�F�N�g�̉摜
	aqua::CSprite      m_MoveKeyLight[(int)CAN_MOVE_ID::MAX];      //! �ړ��ł��������\���摜
	aqua::CSprite      m_MoveKey[(int)CAN_MOVE_ID::MAX];           //! �ړ����邽�߂̃L�[�̉摜

	float              m_EffectRota;                               //! �G�t�F�N�g�̉�]

	CSelectSystem* m_SelectSystem;
	unsigned char  m_LightFrame;                                   //! ���C�g�̋P�x
	unsigned char  m_AlphaReta;

	aqua::CSurface m_BackGroundSurface;
};