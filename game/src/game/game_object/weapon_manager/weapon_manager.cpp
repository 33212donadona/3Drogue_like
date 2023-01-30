#include "weapon_manager.h"
#include "weapon/sowrd/sword.h"
#include "weapon/weapon.h"
#include "weapon/weapon_id.h"
CWeaponManager::CWeaponManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"WeaponManager")
{
}

void CWeaponManager::Initialize()
{
}

void CWeaponManager::Update()
{
}

void CWeaponManager::Finalize()
{
}

void CWeaponManager::SetWeapon(WEAPON_ID weapon_id)
{
	if (weapon_id == m_NowWeapon)return;
	m_Weapon->Finalize();
	switch (weapon_id)
	{
	case WEAPON_ID::SWORD:
		m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
		break;
	case WEAPON_ID::MAGIC:

		break;
	default:
		break;
	}

	m_NowWeapon = weapon_id;
}

bool CWeaponManager::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return false;
}
