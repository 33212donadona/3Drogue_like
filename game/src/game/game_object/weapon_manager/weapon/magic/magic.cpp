#include "magic.h"
#include "../../../unit_manager/unit/player/player.h"

const int CMagic::m_effect_radius = 10;
const int CMagic::m_enemy_radius = 3;

CMagic::CMagic(aqua::IGameObject* parent)
	:IWeapon(parent, "Magic")
	, m_HitMagic(false)
	, m_ShotFlag(false)
	, m_Player(nullptr)
	, m_MoveDistance(0)
	, m_MagicState(MAGIC_STATE::STANDBY)
{
}

void CMagic::Initialize()
{
	m_MagicFirstEffect.Create("data\\effect\\magic_3_first_2.efkefc");
	m_MagicKeepEffect.Create("data\\effect\\magic_3_keep.efkefc");
	m_MagicEndEffect.Create("data\\effect\\magic_3_end.efkefc");
}

void CMagic::Update()
{
	if (!m_Player)
	{
		m_Player = (CPlayer*)aqua::FindGameObject("Player");
	}

	m_HitMagic |= m_MagicKeepEffect.position.x < -98.0f || m_MagicKeepEffect.position.x > 98.0f;
	m_HitMagic |= m_MagicKeepEffect.position.z < -98.0f || m_MagicKeepEffect.position.z > 98.0f;

	if (m_Player)
	{
		switch (m_MagicState)
		{
		case MAGIC_STATE::STANDBY:

			if (m_Player->GetStandbyFlag())
			{
				m_MagicState = MAGIC_STATE::INVOKE_MAGIC;
				m_MagicFirstEffect.Play();
			}

			break;
		case MAGIC_STATE::INVOKE_MAGIC:

			m_MagicFirstEffect.Update();

			if (m_MagicFirstEffect.Finished())
			{
				m_MagicKeepEffect.Play();
				m_MagicKeepEffect.position = m_MagicFirstEffect.position;

				if (!m_Player->GetShotFlag())
					m_MagicState = MAGIC_STATE::STANDBY;
			}

			if (m_Player->GetShotFlag())
			{
				m_MagicState = MAGIC_STATE::KEEP_MAGIC;
				m_MagicKeepEffect.position = m_MagicFirstEffect.position;
				m_MagicKeepEffect.visible = true;
				m_HitMagic = false;
			}
			break;
		case MAGIC_STATE::KEEP_MAGIC:

			if (m_Player->GetAttackFlag() || m_ShotFlag)
			{
				Shot();
				m_ShotFlag = true;
			}
			else
				m_MagicKeepEffect.position = m_MagicFirstEffect.position;

			if (m_HitMagic)
			{
				m_MagicEndEffect.Play();
				m_MagicKeepEffect.visible = false;
				m_ShotFlag = false;
				m_MagicEndEffect.position = m_MagicKeepEffect.position;
				m_MagicState = MAGIC_STATE::FINISHED_MAGIC;
			}

			if (m_MagicKeepEffect.Finished() && !m_HitMagic)
				m_MagicKeepEffect.Play();

			m_MagicKeepEffect.Update();

			break;
		case MAGIC_STATE::FINISHED_MAGIC:
			if (m_MagicEndEffect.Finished())
			{
				m_MagicState = MAGIC_STATE::STANDBY;
				m_MoveDistance = 0;
			}

			m_MagicEndEffect.Update();

			break;
		default:
			break;
		}

		if (m_Player->GetCancelMagic())
		{
			m_MagicState = MAGIC_STATE::STANDBY;
			m_MoveDistance = 0;
		}
	}
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
	distance.x = m_MagicKeepEffect.position.x - enemy_pos.x;
	distance.y = m_MagicKeepEffect.position.z - enemy_pos.z;

	m_HitMagic = distance.x * distance.x + distance.y * distance.y <= r * r;

	return m_HitMagic;
}

void CMagic::SetPosition(aqua::CVector3 position)
{
	m_MagicFirstEffect.position = position;
}

void CMagic::Shot()
{
	m_Angles = m_Player->GetAngle();

	aqua::CVector3 md(sin(m_Angles), 0.0f, cos(m_Angles));

	m_MagicKeepEffect.position -= md;
}