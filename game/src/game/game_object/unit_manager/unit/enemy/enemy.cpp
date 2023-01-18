#include "enemy.h"
#include "../player/player.h"

const float CEnemy::m_max_hit_point = 100.0f;
const float CEnemy::m_attack = 10.0f;

/*
 *  コンストラクタ
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:IUnit(parent, "Enemy")
	, m_DamageFlag(false)
	, m_PlayerModel(nullptr)
{
}
/*
 *  初期化
 */
void CEnemy::Initialize()
{
	m_PlayerModel = (CPlayer*)aqua::FindGameObject("Player");

	m_UnitModel.Create("data\\model\\Enemy", 4);
	m_UnitModel.position = aqua::CVector3(0.0f, 0.0f, 75.0f);
	m_MaxHitPoint = 100.0f;
	
	IUnit::Initialize();
}
/*
 *  更新
 */
void CEnemy::Update()
{
	IUnit::Update();
}
/*
 *  解放
 */
void CEnemy::Finalize()
{
	m_PlayerModel = nullptr;
	IUnit::Finalize();
}

void CEnemy::Damage(float hit_damage)
{
}

void CEnemy::CheckHitDamage(float hit_damage, aqua::CVector3 hit_pos_first, aqua::CVector3 hit_pos_end)
{
	bool gbc = m_UnitModel.GetBoneCollision("mixamorig:Hips", 20, hit_pos_first, hit_pos_end).HitFlag;

	if (!m_DamageFlag && gbc)
		m_DamageFlag = true;

	if (m_DamageFlag)
	{
		Damage(hit_damage);
		if (!gbc)
			m_DamageFlag = false;
	}
}

void CEnemy::Algorithms()
{
	aqua::CVector3 angle = m_UnitModel.position - m_PlayerModel->GetPosition();
	m_UnitModel.angles.x = atan2(angle.x, angle.z);

}
