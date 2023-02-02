#include "weapon_manager.h"
#include "weapon/sowrd/sword.h"
#include "weapon/magic/magic.h"
#include "weapon/weapon_id.h"
CWeaponManager::CWeaponManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "WeaponManager")
	, m_BoneIndex(0)
	, m_BoneName("")
	, m_Weapon(nullptr)
{
}

void CWeaponManager::Initialize()
{
	m_NowWeapon = WEAPON_ID::MAX;
}

void CWeaponManager::Update()
{
	if (m_Weapon)m_Weapon->Update();

	IGameObject::Update();
}

void CWeaponManager::Finalize()
{
	if (m_Weapon)
	{
		m_Weapon->Finalize();
		AQUA_SAFE_DELETE_ARRAY(m_Weapon);
	}
}

void CWeaponManager::SetWeapon(WEAPON_ID weapon_id)
{
	if (weapon_id == m_NowWeapon)return;

	if (m_Weapon)
	{
		m_Weapon->Finalize();
		m_Weapon = nullptr;
	}
	switch (weapon_id)
	{
	case WEAPON_ID::FIST:

		break;

	case WEAPON_ID::SWORD:
		m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
		break;

	case WEAPON_ID::MAGIC:
		m_Weapon = (IWeapon*)aqua::CreateGameObject<CMagic>(this);
		break;

	case WEAPON_ID::MONEY:

		break;

	default:
		break;
	}
	if (m_Weapon)
		m_Weapon->Initialize();

	m_NowWeapon = weapon_id;
}

bool CWeaponManager::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	if (!m_Weapon)return false;

	bool hit_flag;

	switch (m_NowWeapon)
	{
	case WEAPON_ID::FIST:
		hit_flag = m_Weapon->CheckHit(first_pos);
		break;

	case WEAPON_ID::SWORD:
		hit_flag = m_Weapon->CheckHit(first_pos, end_pos);
		break;

	case WEAPON_ID::MAGIC:
		hit_flag = m_Weapon->CheckHit(first_pos);
		break;

	case WEAPON_ID::MONEY:
		hit_flag = m_Weapon->CheckHit(first_pos);
		break;

	default:
		hit_flag = false;
		break;
	}

	return hit_flag;
}

void CWeaponManager::SetHandMatrix(aqua::CModel& model, std::string hand_name)
{
	if (hand_name == "")return;
	;
	if (m_BoneName != hand_name)
	{
		m_BoneName = hand_name;

		m_BoneIndex = model.GetBoneIndex(m_BoneName);
	}

	switch (m_NowWeapon)
	{
	case WEAPON_ID::FIST:

		break;

	case WEAPON_ID::SWORD:
		m_Weapon->SetMatrix(model.GetBoneMatrix(m_BoneIndex));
		break;

	case WEAPON_ID::MAGIC:
		m_Weapon->SetPosition(model.GetBonePosition(m_BoneIndex));
		break;

	case WEAPON_ID::MONEY:

		break;

	default:
		break;
	}

}
