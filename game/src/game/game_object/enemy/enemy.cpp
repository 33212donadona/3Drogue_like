#include "enemy.h"
#include "../unit/unit.h"

const float CEnemy::m_max_hit_point = 100.0f;
const float CEnemy::m_attack = 10.0f;

/*
 *  コンストラクタ
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Enemy")
	, m_DamageFlag(false)
	, m_UnitModel(nullptr)
	, m_EnemyState(nullptr)
{
}
/*
 *  初期化
 */
void CEnemy::Initialize()
{
	m_UnitModel = (CUnit*)aqua::FindGameObject("Unit");

	m_EnemyModel.Create("data\\model\\Enemy", 4);
	m_EnemyModel.scale = aqua::CVector3::ONE * 0.1f;
	m_EnemyModel.position = aqua::CVector3(0.0f, 0.0f, 75.0f);
	m_EnemyModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
}
/*
 *  更新
 */
void CEnemy::Update()
{
	aqua::CVector3 angle = m_EnemyModel.position - m_UnitModel->GetPosition();
	m_EnemyModel.angles.x = atan2(angle.x, angle.z);
	m_EnemyModel.AnimationUpdata();
}
/*
 *  解放
 */
void CEnemy::Finalize()
{
	m_EnemyModel.Delete();
	m_UnitModel = nullptr;
	m_EnemyState = nullptr;
}

void CEnemy::Damage(float hit_damage)
{
	if (m_EnemyState)
	{
		aqua::IGameObject::DeleteObject();
	}
}

void CEnemy::Damage(float hit_damage, aqua::CVector3 hit_pos_first, aqua::CVector3 hit_pos_end)
{
	bool gbc = m_EnemyModel.GetBoneCollision("mixamorig:Hips", 20, hit_pos_first, hit_pos_end).HitFlag;

	if (!m_DamageFlag && gbc)
		m_DamageFlag = true;

	if (m_DamageFlag)
	{
		Damage(hit_damage);
		if (!gbc)
			m_DamageFlag = false;
	}
}