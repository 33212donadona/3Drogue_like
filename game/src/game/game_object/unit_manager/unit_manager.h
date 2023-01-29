#pragma once
#include "aqua.h"

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
	std::list<CEnemy*> m_EnemyList;
	int m_EnemyDeleteCount;
};

