#include "money_weapon.h"
#include "../../../bag/bag_data.h"
#include "../../../unit_manager/unit/player/player.h"
#include "../../../input/input.h"

const int CMoneyWeapon::m_money_radius = 18;
const int CMoneyWeapon::m_enemy_radius = 3;

CMoneyWeapon::CMoneyWeapon(aqua::IGameObject* parent)
	:IWeapon(parent, "MoneyWeapon")
	, m_Player(nullptr)
	, m_BagData(nullptr)
{
}

void CMoneyWeapon::Initialize()
{
	m_MoneyEffect.Create("data\\effect\\coin_attack.efkefc");
	m_MoneyEffect.scale = aqua::CVector3::ONE * 10.0f;
	m_BagData = (CBagData*)aqua::FindGameObject("BagData");
}

void CMoneyWeapon::Update()
{
	if (!m_Player)
	{
		m_Player = (CPlayer*)aqua::FindGameObject("Player");
	}

	if (m_Player)
	{
		if (m_Player->GetAttackFlag())
		{
			m_MoneyEffect.rotation.y = m_Player->GetAngle();
			m_MoneyEffect.position = m_MoneyPosition;
			m_MoneyEffect.Play();
		}

	}

	m_MoneyEffect.Update();
}

void CMoneyWeapon::Finalize()
{
	m_MoneyEffect.Delete();
}

bool CMoneyWeapon::CheckHit(aqua::CVector3 enemy_pos)
{
	float r = m_money_radius + m_enemy_radius;
	bool  hit = false;

	aqua::CVector2 distance;
	distance.x = m_MoneyPosition.x - enemy_pos.x;
	distance.y = m_MoneyPosition.z - enemy_pos.z;

	hit = distance.x * distance.x + distance.y * distance.y <= r * r;

	if (hit && m_Player)
	{
		aqua::CVector3 angle = enemy_pos - m_MoneyPosition;
		float theta = atan2(angle.x, angle.z);

		float angular_difference = 15.0f + aqua::RadToDeg(m_Player->GetAngle()) - aqua::RadToDeg(theta);

		m_HitMoney = abs(angular_difference) < 15.0f;
	}
	else
		m_HitMoney = false;

	return m_HitMoney;
}

void CMoneyWeapon::SetPosition(aqua::CVector3 position)
{
	m_MoneyPosition = position;
}
