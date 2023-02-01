#pragma once
#include "aqua.h"

class IWeapon :public aqua::IGameObject
{
public:

	IWeapon(aqua::IGameObject* parent,std::string name);
	~IWeapon() = default;

	virtual void Initialize()override {};
	virtual void Update()override {};
	virtual void Finalize()override {};

	virtual bool CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos) { return false; };
	virtual bool CheckHit(aqua::CVector3 enemy_pos) { return false; };
	virtual void SetMatrix(aqua::CMatrix matrix){};
	virtual void SetPosition(aqua::CVector3 position) {};
};