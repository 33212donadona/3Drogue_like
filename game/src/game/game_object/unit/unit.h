#pragma once
#include "aqua.h"
#include "../weapon_manager/weapon/weapon.h"
#include "../weapon_manager/weapon/sword/sword.h"
#include "../weapon_manager/weapon/magic/magic_stick.h"

class CUnit : public aqua::IGameObject
{
public:

	CUnit(aqua::IGameObject* parent);
	~CUnit() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

	int GetAnimetionNum();

	aqua::CVector3 GetPosition();

private:
	static const int m_max_animetion;
	void AnimetionWork();

	aqua::CModel m_UnitModel;
	IWeapon* m_Weapon;
	float m_Angles;
	int Animetion;
};