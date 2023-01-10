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
	//m_WeaponModel.position = m_ModelPosition;
	m_WeaponModel.SetBoneMatrix(m_ModelMatrix);
	m_WeaponModel.scale = m_ModelScale;
}

void IWeapon::Finalize()
{
	m_WeaponModel.Delete();
}
