#include "magic.h"
#include "../../../unit_manager/unit/player/player.h"

const int CMagic::m_effect_radius = 3;
const int CMagic::m_enemy_radius = 3;

CMagic::CMagic(aqua::IGameObject* parent)
	:IWeapon(parent, "Magic")
	, m_HitMagic(false)
	, m_FindPlayer(false)
	, m_MoveDistance(0)
{
}

void CMagic::Initialize()
{
	m_MagicFirstEffect.Create("data\\effect\\magic_3_first.efkefc");
	m_MagicKeepEffect.Create("data\\effect\\magic_3_keep.efkefc");
	m_MagicEndEffect.Create("data\\effect\\magic_3_end.efkefc");
	m_MagicFirstEffect.Play();
}

void CMagic::Update()
{
	if (!m_FindPlayer)
	{
		m_Player = (CPlayer*)aqua::FindGameObject("Player");
		m_FindPlayer = true;
	}

	if (m_MagicFirstEffect.Finished())
		m_MagicKeepEffect.Play();

	if (m_MagicKeepEffect.Finished())
		m_MagicKeepEffect.Play();

	if (m_HitMagic)
		m_MagicEndEffect.Play();



	m_MagicFirstEffect.Update();
}

void CMagic::Finalize()
{
	m_MagicFirstEffect.Delete();
	m_MagicKeepEffect.Delete();
	m_MagicEndEffect.Delete();
}

bool CMagic::CheckHit(aqua::CVector3 enemy_pos)
{
	float r = m_effect_radius + m_enemy_radius;

	aqua::CVector2 distance;
	distance.x = m_MagicFirstEffect.position.x - enemy_pos.x;
	distance.y = m_MagicFirstEffect.position.z - enemy_pos.z;

	m_HitMagic = distance.x * distance.x + distance.y * distance.y <= r * r;

	return m_HitMagic;
}

void CMagic::SetPosition(aqua::CVector3 position)
{
	m_MagicFirstEffect.position = position;
	m_MagicEndEffect.position = position;
}

void CMagic::Shot()
{
	if (m_Player->GetAttackFlag())
		m_Angles = m_Player->GetAngle();

	m_MoveDistance++;

	aqua::CVector3 md(sin(m_Angles), 0.0f, cos(m_Angles))* m_MoveDistance;

	m_MagicKeepEffect.position = m_MagicFirstEffect.position;
}
