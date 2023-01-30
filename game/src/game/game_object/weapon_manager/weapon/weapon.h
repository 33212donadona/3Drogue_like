#pragma once
#include "aqua.h"

class IWeapon :public aqua::IGameObject
{
public:

	IWeapon(aqua::IGameObject* parent,std::string name);
	~IWeapon() = default;

	virtual bool CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos) { return false; };
};