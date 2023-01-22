#include "weapon.h"

IWeapon::IWeapon(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,"Weapon", name)
{
}

void IWeapon::Initialize()
{

	m_WeaponModel.Create(m_WeaponFileName,0);
}

void IWeapon::Update()
{
	m_WeaponModel.SetMatrix(m_RotationMatrix * m_RotationMatrix2 * m_ModelMatrix);
}

void IWeapon::Finalize()
{
	m_WeaponModel.Delete();
}

void IWeapon::SetMatrix(aqua::CMatrix model_matrix)
{
	m_ModelMatrix = model_matrix;
}

bool IWeapon::CheckHitWeapon(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_WeaponModel.GetBoneCapsuleCollision("Collision.000",first_pos, end_pos,3).HitFlag || m_WeaponModel.GetBoneCapsuleCollision("Collision.001", first_pos, end_pos, 3).HitFlag;
}