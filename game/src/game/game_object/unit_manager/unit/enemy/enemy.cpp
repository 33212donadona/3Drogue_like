#include "enemy.h"
#include "../player/player.h"
const float CEnemy::m_max_hit_point = 100.0f;
const float CEnemy::m_attack = 10.0f;

/*
 *  コンストラクタ
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:IUnit(parent, "Enemy")
	, m_DamageFlag(true)
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
	m_HitPoint = 100.0f;
	
	IUnit::Initialize();
}
/*
 *  更新
 */
void CEnemy::Update()
{
	Algorithms();

	if (m_PlayerModel->CheckHit(m_UnitModel.GetBonePosistion(6), m_UnitModel.GetBonePosistion(69)) && !m_DamageFlag)
	{
		m_HitPoint -= 100.0f;
		m_DamageFlag = true;
	}

	if (m_DamageFlag)
	{
		if (!m_PlayerModel->CheckHit(m_UnitModel.GetBonePosistion(6), m_UnitModel.GetBonePosistion(69)))
			m_DamageFlag = false;
	}

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

void CEnemy::Algorithms()
{
	aqua::CVector3 angle = m_UnitModel.position - m_PlayerModel->GetPosition();
	m_UnitModel.angles = atan2(angle.x, angle.z);

}