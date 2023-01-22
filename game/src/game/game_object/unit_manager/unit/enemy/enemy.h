#pragma once
#include "aqua.h"
#include "../unit.h"

class CPlayer;
class IWeapon;

class CEnemy : public IUnit
{
public:
	CEnemy(aqua::IGameObject* parent);
	~CEnemy() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	void Damage(float hit_damage);
	void CheckHitDamage(float hit_damage, aqua::CVector3 hit_pos_first, aqua::CVector3 hit_pos_end);

private:
	void Algorithms();
	static const float m_max_hit_point;
	static const float m_attack;
	IWeapon* m_Weapon;
	CPlayer* m_PlayerModel;
	bool m_DamageFlag;            //! 連続ダメージを防ぐ
};