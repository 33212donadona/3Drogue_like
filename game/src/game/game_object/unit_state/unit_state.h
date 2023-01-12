#pragma once
#include "aqua.h"

class CStateData : public aqua::IGameObject
{
public:
	CStateData(aqua::IGameObject* parent);
	~CStateData() = default;

	void Set(float max_hit_point, float attack = 10.0f);

	void  Damage(float damage);

	float GetAttack();
	float GetHitPoint();

private:
	float m_MaxHitPoint;
	float m_HitPoint;
	float m_Attack;

};