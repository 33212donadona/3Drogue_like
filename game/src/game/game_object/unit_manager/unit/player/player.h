#pragma once
#include "aqua.h"
#include "../../../weapon_manager/weapon/weapon.h"
#include "../../../weapon_manager/weapon/sword/sword.h"
#include "../../../weapon_manager/magic/magic.h"
#include "../../../weapon_manager/magic/fire_ball/fire_ball.h"
#include "../unit.h"

class CEnemy;
class CStage;

class CPlayer : public IUnit
{
public:

	CPlayer(aqua::IGameObject* parent);
	~CPlayer() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	int GetAnimetionNum();

private:

	void AnimetionWork();       //! アニメーション
	void Move();                //! 移動
	void Rotation();            //! 回転
	void Weapon();              //! 武器
	void Collision();           //! 衝突処理

private:
	static const int m_max_animetion;
	static const float m_shot_animetion_frame;
	static const float m_max_hit_point;
	static const float m_attack;


	IWeapon* m_Weapon;
	IMagic* m_Magic;
	CStage* m_Stage;
	float m_Angles;
	int   m_MagicFrame;
	int Animetion;

	bool m_ShotMagic;
};