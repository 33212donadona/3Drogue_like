#include "enemy.h"
#include "../player/player.h"
#include "../../../stage/stage.h"

const float CEnemy::m_max_hit_point = 280.0f;
const float CEnemy::m_attack = 10.0f;

/*
 *  �R���X�g���N�^
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:IUnit(parent, "Enemy")
	, m_DamageFlag(true)
	, m_AnimetionID(ENEMY_ANIME_ID::IDEL)
	, m_PlayerModel(nullptr)
{
}
/*
 *  ������
 */
void CEnemy::Initialize()
{
	m_PlayerModel = (CPlayer*)aqua::FindGameObject("Player");

	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	m_UnitModel.Create("data\\model\\Enemy", (int)ENEMY_ANIME_ID::MAX);
	m_Sword.Create("data\\model\\weapon\\sword", 0);

	m_UnitModel.AttachAnimation((int)m_AnimetionID);

	m_Sword.SetMatrix(m_UnitModel.GetBoneMatrix("mixamorig:RightHandThumb1"));

	m_HitPoint = m_max_hit_point;

	m_Attack = 25.0f;

	m_AttackCoolTime.Setup(3.0f);
	m_AttackCoolTime.SetTime(m_AttackCoolTime.GetLimit());

	//�����ʒu�ݒ�
	while (m_UnitModel.position == aqua::CVector3::ZERO)
	{
		m_UnitModel.position = m_Stage->GetArePosition(aqua::CPoint(aqua::Rand(21, 1), aqua::Rand(21, 1)));
	}

	IUnit::Initialize();
}
/*
 *  �X�V
 */
void CEnemy::Update()
{
	IUnit::Update();

	if (m_AnimetionID == ENEMY_ANIME_ID::DAMAGE && m_UnitModel.AnimetionFinished())
	{
		m_AnimetionID = ENEMY_ANIME_ID::IDEL;
	}

	m_Sword.SetMatrix(m_UnitModel.GetBoneMatrix("mixamorig:RightHandThumb1"));

	m_UnitModel.AttachAnimation((int)m_AnimetionID);
}
/*
 *  ���
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
			GetState() != STATE::DAMAGE
			)
		{
			m_HitPoint -= m_PlayerModel->GetAttack();
			m_DamageFlag = true;
			m_AnimetionID = ENEMY_ANIME_ID::DAMAGE;
		}
	}

	if (m_DamageFlag)
	{
		if (!m_PlayerModel->CheckHit(m_UnitModel.GetBonePosition(6), m_UnitModel.GetBonePosition(69)))
			m_DamageFlag = false;
	}

}

void CEnemy::Algorithms()
{
	aqua::CVector2 distance;
	float r1 = 3 + 40;
	float r2 = 3 + 10;
	float d;

	distance.x = m_UnitModel.position.x - m_PlayerModel->GetPosition().x;
	distance.y = m_UnitModel.position.z - m_PlayerModel->GetPosition().z;

	r1 *= r1;
	r2 *= r2;

	d = distance.x * distance.x + distance.y * distance.y;

	if (d <= r2 && m_AttackCoolTime.Finished())
	{
		m_AnimetionID = ENEMY_ANIME_ID::ATTACK;

		aqua::CVector3 end_pos = m_PlayerModel->GetPosition();
		end_pos.y = 77.0f;

		if (m_Sword.GetBoneCapsuleCollision("Collision.000", m_PlayerModel->GetPosition(), end_pos, 3).HitFlag ||
			m_Sword.GetBoneCapsuleCollision("Collision.001", m_PlayerModel->GetPosition(), end_pos, 3).HitFlag)
		{
			m_PlayerModel->HitEnemyAttack(m_Attack);
			m_AttackCoolTime.Reset();
			m_AnimetionID = ENEMY_ANIME_ID::IDEL;
		}
	}
	else if (d <= r1 && d > r2)
	{
		m_AnimetionID = ENEMY_ANIME_ID::RUN;

		aqua::CVector3 angle = m_UnitModel.position - m_PlayerModel->GetPosition();
		m_UnitModel.angles = atan2(angle.x, angle.z);

		aqua::CVector3 md(sin(m_UnitModel.angles), 0.0f, cos(m_UnitModel.angles));

		m_UnitModel.position -= md * 0.5f;
	}


	m_AttackCoolTime.Update();
}

void CEnemy::AnimetionWark()
{

}
