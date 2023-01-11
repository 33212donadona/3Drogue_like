#include "sword.h"

CSword::CSword(aqua::IGameObject* parent)
	:IWeapon(parent,"Sword")
{
}

void CSword::Initialize()
{
	m_WeaponFileName = "data\\model\\weapon\\sword";
	m_RotationMatrix.AxisRotation(aqua::CVector3(1.0f, 0.0f, 0.0f), aqua::DegToRad(90));
	m_RotationMatrix2.AxisRotation(aqua::CVector3(0.0f,0.0f, 1.0f), aqua::DegToRad(90));

	IWeapon::Initialize();
}

void CSword::Update()
{
	IWeapon::Update();
}

void CSword::Finalize()
{
	IWeapon::Finalize();
}
