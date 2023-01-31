#include "magic.h"
const int CMagic::m_effect_radius = 3;
const int CMagic::m_enemy_radius = 3;

CMagic::CMagic(aqua::IGameObject* parent)
	:IWeapon(parent, "Magic")
{
}

void CMagic::Initialize()
{
	m_MagicEffect.Create("data\\effect\\magic_2.efkefc");
}

void CMagic::Update()
{
}

void CMagic::Finalize()
{
	m_MagicEffect.Delete();
}

bool CMagic::CheckHit(aqua::CVector3 enemy_pos)
{
	float r = m_effect_radius + m_enemy_radius;
	aqua::CVector2 distance;
	distance.x = m_MagicEffect.position.x - enemy_pos.x;
	distance.y = m_MagicEffect.position.z - enemy_pos.z;

	return distance.x * distance.x + distance.y * distance.y <= r * r;
}

void CMagic::SetPosition(aqua::CVector3 position)
{
	m_MagicEffect.position = position;
}
