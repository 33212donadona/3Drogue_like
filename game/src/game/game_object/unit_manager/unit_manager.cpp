#include "unit_manager.h"
#include "unit/player/player.h"
#include "unit/enemy/enemy.h"
#include "../job_manager/job_id.h"
#include "../common_data/common_data.h"

CUnitManager::CUnitManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "UnitManager")
	, m_PlayerDead(false)
{
}
/*
* 初期化
*/
void CUnitManager::Initialize()
{
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_CWeaponManager = aqua::CreateGameObject<CWeaponManager>(this);
	m_Player = aqua::CreateGameObject<CPlayer>(this);

	int enemy_list_size = (int)m_CommonData->GetData().stage_lever * 2 + 1;

	for (int i = 0; i < enemy_list_size; i++)
		m_EnemyList.push_back(aqua::CreateGameObject<CEnemy>(this));

	m_EnemyDeleteCount = (int)m_EnemyList.size();

	m_Player->Initialize();

	for (auto& elem : m_EnemyList)
		elem->Initialize();
}
/*
* 更新
*/
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
/*
* 解放
*/
void CUnitManager::Finalize()
{
	IGameObject::Finalize();
	
	if (!m_EnemyList.empty())
		m_EnemyList.clear();
}
/*
* 敵がゼロ体かどうか
*/
bool CUnitManager::EmptyEnemyList()
{
	return m_EnemyList.empty();
}
/*
* プレイヤーの死亡確認
*/
bool CUnitManager::GetPlayerDead()
{
	if (!m_Player)return m_PlayerDead;
	m_PlayerDead = m_Player->GetDead();
	return m_PlayerDead;
}
/*
* プレイヤーに職業を設定
*/
void CUnitManager::SetPlayerJob(JOB_ID job_id)
{
	JOB_ID id = (JOB_ID)((int)job_id % (int)JOB_ID::MAX);

	m_Player->SetJodID(id);
}
