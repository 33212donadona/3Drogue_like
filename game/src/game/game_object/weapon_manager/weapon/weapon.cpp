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

void IWeapon::SetMatrix(aqua::CMatrix mm)
{
	m_ModelMatrix = mm;
}
