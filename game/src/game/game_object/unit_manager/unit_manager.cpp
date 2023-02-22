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
* ������
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
* �X�V
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
* ���
*/
void CUnitManager::Finalize()
{
	IGameObject::Finalize();
	
	if (!m_EnemyList.empty())
		m_EnemyList.clear();
}
/*
* �G���[���̂��ǂ���
*/
bool CUnitManager::EmptyEnemyList()
{
	return m_EnemyList.empty();
}
/*
* �v���C���[�̎��S�m�F
*/
bool CUnitManager::GetPlayerDead()
{
	if (!m_Player)return m_PlayerDead;
	m_PlayerDead = m_Player->GetDead();
	return m_PlayerDead;
}
/*
* �v���C���[�ɐE�Ƃ�ݒ�
*/
void CUnitManager::SetPlayerJob(JOB_ID job_id)
{
	JOB_ID id = (JOB_ID)((int)job_id % (int)JOB_ID::MAX);

	m_Player->SetJodID(id);
}
