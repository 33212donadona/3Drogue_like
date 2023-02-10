#include "enemy.h"
#include "../player/player.h"
#include "../../../stage/stage.h"

const float CEnemy::m_max_hit_point = 280.0f;
const float CEnemy::m_attack = 10.0f;

/*
 *  コンストラクタ
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:IUnit(parent, "Enemy")
	, m_DamageFlag(true)
	, m_AnimetionID(ENEMY_ANIME_ID::IDEL)
	, m_PlayerModel(nullptr)
{
}
/*
 *  初期化
 */
void CEnemy::Initialize()
{
	m_PlayerModel = (CPlayer*)aqua::FindGameObject("Player");

	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	m_UnitModel.Create("data\\model\\Enemy", (int)ENEMY_ANIME_ID::MAX);
	m_UnitModel.AttachAnimation((int)m_AnimetionID);

	m_HitPoint = m_max_hit_point;

	//初期位置設定
	while (m_UnitModel.position == aqua::CVector3::ZERO)
	{
		m_UnitModel.position = m_Stage->GetArePosition(aqua::CPoint(aqua::Rand(21, 1), aqua::Rand(21, 1)));
	}

	IUnit::Initialize();
}
/*
 *  更新
 */
void CEnemy::Update()
{

	IUnit::Update();

	m_UnitModel.AnimationUpdata();
}
/*
 *  解放
 */
void CEnemy::Finalize()
{
	m_PlayerModel = nullptr;
	IUnit::Finalize();
}

void CEnemy::MoveUpdata()
{
	Algorithms();

	if (GetState() != STATE::DEAD)
	{
		if (
			m_PlayerModel->CheckHit(m_UnitModel.GetBonePosition(6), m_UnitModel.GetBonePosition(69)) &&
			!m_DamageFlag &&
			GetState() != IUnit::STATE::DAMAGE
			)
		{
			m_HitPoint -= m_PlayerModel->GetAttack();
			m_DamageFlag = true;
			m_AnimetionID = ENEMY_ANIME_ID::DAMAGE;
		}
	}
	else
		m_AnimetionID = ENEMY_ANIME_ID::DAMAGE;

	if (m_DamageFlag)
	{
		if (!m_PlayerModel->CheckHit(m_UnitModel.GetBonePosition(6), m_UnitModel.GetBonePosition(69)))
			m_DamageFlag = false;
	}

	if (m_AnimetionID == ENEMY_ANIME_ID::DAMAGE)
	{
		if (m_UnitModel.AnimetionFinished())
			m_AnimetionID = ENEMY_ANIME_ID::IDEL;

	}

	m_UnitModel.AttachAnimation((int)m_AnimetionID);
}

void CEnemy::Algorithms()
{
	aqua::CVector3 angle = m_UnitModel.position - m_PlayerModel->GetPosition();
	m_UnitModel.angles = atan2(angle.x, angle.z);
}

void CEnemy::AnimetionWark()
{

}
