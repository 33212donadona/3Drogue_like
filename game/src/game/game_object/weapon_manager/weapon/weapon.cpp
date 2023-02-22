#include "weapon.h"

/*
* コンストラクタ
*/
IWeapon::IWeapon(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,name,"Weapon")
{
}