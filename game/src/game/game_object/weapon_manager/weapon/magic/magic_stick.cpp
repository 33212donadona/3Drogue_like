#include "magic_stick.h"

CMagicStick::CMagicStick(aqua::IGameObject* parent)
	:IWeapon(parent,"MagicStick")
{
}

void CMagicStick::Initialize()
{
	m_WeaponFileName = "data\\model\\weapon\\magic_stick";
	m_RotationMatrix.AxisRotation(aqua::CVector3(1.0f, 0.0f, 0.0f), aqua::DegToRad(180));

	IWeapon::Initialize();
}

void CMagicStick::Update()
{
	IWeapon::Update();
}

void CMagicStick::Finalize()
{
	IWeapon::Finalize();
}
