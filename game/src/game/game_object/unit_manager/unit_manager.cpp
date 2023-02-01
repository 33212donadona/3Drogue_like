#include "unit_manager.h"
#include "unit/player/player.h"
#include "unit/enemy/enemy.h"


CUnitManager::CUnitManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "UnitManager")
{
}

void CUnitManager::Initialize()
{
	m_CWeaponManager = aqua::CreateGameObject<CWeaponManager>(this);

	m_Player = aqua::CreateGameObject<CPlayer>(this);
	m_EnemyList.push_back(aqua::CreateGameObject<CEnemy>(this));

	m_EnemyDeleteCount = (int)m_EnemyList.size();
	IGameObject::Initialize();
}

void CUnitManager::Update()
{
	m_Player->Update();

	int enemy = 0;

	if (!m_EnemyList.empty())
	{
		for (auto& elem : m_EnemyList)
		{
			if (elem->GetDead())
				enemy++;
			else
				elem->Update();
		}
	}

	if (enemy == m_EnemyDeleteCount)
	{
		for (auto& elem : m_EnemyList)
		{
			elem->Finalize();
		}
		m_EnemyList.clear();
	}

	m_CWeaponManager->Update();
}

void CUnitManager::Finalize()
{
	IGameObject::Finalize();
}

bool CUnitManager::EmptyEnemyList()
{
	return m_EnemyList.empty();
}