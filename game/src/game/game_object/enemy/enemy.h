#pragma once
#include "aqua.h"

class CUnit;
class CStateData;

class CEnemy : public aqua::IGameObject
{
public:
	CEnemy(aqua::IGameObject* parent);
	~CEnemy() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	void Damage(float hit_damage);
	void Damage(float hit_damage, aqua::CVector3 hit_pos_first, aqua::CVector3 hit_pos_end);

private:
	static const float m_max_hit_point;
	static const float m_attack;

	aqua::CModel m_EnemyModel;
	CUnit* m_UnitModel;
	CStateData* m_EnemyState;
	bool m_DamageFlag;            //! 連続ダメージを防ぐ
};