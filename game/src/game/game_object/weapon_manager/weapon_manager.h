#pragma once
#include "aqua.h"

enum class WEAPON_ID;

class CWeaponManager :public aqua::IGameObject
{
public:

	CWeaponManager(aqua::IGameObject* parent);
	~CWeaponManager() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

	void CreateWeapon();

private:

};