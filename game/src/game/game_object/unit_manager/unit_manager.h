#pragma once
#include "aqua.h"
#include "../weapon_manager/weapon_manager.h"

class IUnit;
class CEnemy;
class CPlayer;

class CUnitManager :public aqua::IGameObject
{
public:

	CUnitManager(aqua::IGameObject* parent);
	~CUnitManager() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool EmptyEnemyList();

private:
	CPlayer* m_Player;
	CWeaponManager* m_CWeaponManager;
	std::list<CEnemy*> m_EnemyList;
	int m_EnemyDeleteCount;
};

