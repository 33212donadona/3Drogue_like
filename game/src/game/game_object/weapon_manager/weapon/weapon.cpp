#include "weapon.h"


IWeapon::IWeapon(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,name,"Weapon")
{
}