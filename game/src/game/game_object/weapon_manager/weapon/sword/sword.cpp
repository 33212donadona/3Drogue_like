#include "sword.h"

CSword::CSword(aqua::IGameObject* parent)
	:IWeapon(parent,"Sword")
{
}

void CSword::Initialize()
{
	m_WeaponFileName = "data\\model\\weapon\\sword";
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
