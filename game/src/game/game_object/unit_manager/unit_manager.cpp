#include "unit_manager.h"
#include "unit/player/player.h"
#include "unit/enemy/enemy.h"


CUnitManager::CUnitManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"UnitManager")
{
}

void CUnitManager::Initialize()
{
	m_Player = aqua::CreateGameObject<CPlayer>(this);
	m_EnemyList.push_back(aqua::CreateGameObject<CEnemy>(this));

	IGameObject::Initialize();
}

void CUnitManager::Update()
{
	m_Player->Update();
	for (auto& elem : m_EnemyList)
	{
		elem->Update();
	}
}

void CUnitManager::Finalize()
{
	IGameObject::Finalize();
}

