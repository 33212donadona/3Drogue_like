#include "money_weapon.h"
#include "../../../bag/bag_data.h"
#include "../../../sound_manager/game_sound_manager.h"
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
	m_MoneyCollision.Create("data\\model\\weapon\\coin_collision", 0);
	m_MoneyCollision.axis.y = 1.0f;
	m_MoneyCollision.initial_axis.y = 1.0f;
	m_MoneyCollision.initial_angles = aqua::DegToRad(180);
	m_MoneyCollision.position.y = -50.0f;
	m_MoneyCollision.scale = aqua::CVector3::ONE * 0.05f;
	m_MoneyCollision.ChengeFrameVisible("Collition", false);
	m_BagData = (CBagData*)aqua::FindGameObject("BagData");
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
}

void CMoneyWeapon::Update()
{
	if (!m_Player)
	{
		m_Player = (CPlayer*)aqua::FindGameObject("Player");
	}

	if (m_Player)
	{
		if (m_Player->GetShotFlag())
		{
			m_MoneyEffect.rotation.y = m_Player->GetAngle();
			m_MoneyEffect.position = m_MoneyPosition;
			m_MoneyCollision.position = m_MoneyPosition;
			m_MoneyCollision.angles = m_Player->GetAngle();

			m_MoneyEffect.Play();
			m_BagData->AddToDepositBalance(-25);
		}

		if (m_MoneyEffect.Finished() || m_HitMoney)
			m_MoneyCollision.position.y = -50.0f;

	}

	m_MoneyEffect.Update();
}

void CMoneyWeapon::Finalize()
{
	m_MoneyCollision.Delete();
	m_MoneyEffect.Delete();
}

bool CMoneyWeapon::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	m_HitMoney = m_MoneyCollision.GetBoneCapsuleCollision("Collition", first_pos, end_pos, 3).HitFlag;

	return m_HitMoney;
}

void CMoneyWeapon::SetPosition(aqua::CVector3 position)
{
	m_MoneyPosition = position;
}
