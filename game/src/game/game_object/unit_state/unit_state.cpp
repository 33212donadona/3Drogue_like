#include "unit_state.h"

CStateData::CStateData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "StateData")
	, m_MaxHitPoint(0.0f)
	, m_HitPoint(0.0f)
	, m_Attack(0.0f)
{

}
void CStateData::Set(float max_hit_point, float attack)
{
	m_MaxHitPoint = max_hit_point;
	m_HitPoint = max_hit_point;
	m_Attack = attack;
}

void CStateData::Damage(float damage)
{
	m_HitPoint -= damage;
}

float CStateData::GetAttack()
{
	return m_Attack;
}

float CStateData::GetHitPoint()
{
	return m_HitPoint;
}
