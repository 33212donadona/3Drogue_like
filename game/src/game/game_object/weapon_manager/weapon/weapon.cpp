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
	aqua::CMatrix m;
	m.AxisRotation(aqua::CVector3(1.0f, 0.0f, 0.0f),aqua::DegToRad(-45));
	m_WeaponModel.SetBoneMatrix(m * m_ModelMatrix);
	m_WeaponModel.scale = m_ModelScale;
}

void IWeapon::Finalize()
{
	m_WeaponModel.Delete();
}
