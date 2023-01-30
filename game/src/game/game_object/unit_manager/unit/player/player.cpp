#include "player.h"
#include "../enemy/enemy.h"
#include "../../../stage/stage.h"
#include "../../../input/input.h"

const int CPlayer::m_max_animetion = 6;
const float CPlayer::m_shot_animetion_frame = 50.0f;
const float CPlayer::m_max_hit_point = 50.0f;
const float CPlayer::m_attack = 50.0f;

/*
 *  �R���X�g���N�^
 */
CPlayer::CPlayer(aqua::IGameObject* parent)
	:IUnit(parent, "Player")
	, m_Angles(0.0f)
	, m_Attack(false)
	, m_ShotMagic(false)
	, m_Weapon(nullptr)
{
}
/*
 *  ������
 */
void CPlayer::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", m_max_animetion);
	m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
	Animetion = 2;
	
	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	//�����ʒu�ݒ�
	while (m_UnitModel.position == aqua::CVector3::ZERO)
	{
		m_UnitModel.position = m_Stage->GetArePosition(aqua::CPoint(aqua::Rand(21, 1), aqua::Rand(21, 1)));
	}

	m_UnitModel.AttachAnimation(Animetion);

	if (m_Weapon)m_Weapon->Initialize();

	m_HitPoint = 100;

	IUnit::Initialize();
}

/*
 *  �X�V
 */
void CPlayer::Update()
{
	AnimetionWork();

	Weapon();

	IUnit::Update();
}
/*
 *  ���
 */
void CPlayer::Finalize()
{
	if (m_Weapon)m_Weapon->Finalize();

	IUnit::Finalize();
}
/*
*  �����̍X�V
*/
void CPlayer::MoveUpdata()
{
	Move();

	Rotation();
}
/*
 *  �A�j���[�V�����ԍ�
 */
int CPlayer::GetAnimetionNum()
{
	return Animetion;
}

bool CPlayer::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_Weapon->CheckHit(first_pos, end_pos) && Input::Button(Input::KEY_ID::B);
}

/*
 *  �A�j���[�V�����̍X�V
 */
void CPlayer::AnimetionWork()
{
	if (!m_Attack)
	{
		if (Input::Horizotal() || Input::Vertical())
			Animetion = 2;
		else
			Animetion = 0;
	}

	if (!Input::Horizotal() || !Input::Vertical())
		if (Input::In(Input::KEY_ID::B) && !m_Attack)
		{
			m_Attack = true;
			Animetion = 3;
		}

	m_UnitModel.AttachAnimation(Animetion);

	if (m_Attack && m_UnitModel.AnimetionFinished())
	{
		m_Attack = false;
		Animetion = 0;
	}
}
/*
*   �ړ�
*/
void CPlayer::Move()
{
	float x = -Input::Horizotal();
	float z = Input::Vertical();

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3(x * 4.5f, 0.0f, 0.0f)))
		x = 0.0f;

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3(0.0f, 0.0f, z * 4.5f)))
		z = 0.0f;

	if (Input::Button(Input::KEY_ID::B))
	{
		x = 0.0f;
		z = 0.0f;
	}
	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x + x, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z + z, -95.0f, 95.0f);
}

/*
*   ��]
*/
void CPlayer::Rotation()
{
	if (!Input::Button(Input::KEY_ID::B))
		if (Input::Horizotal() || Input::Vertical())
			m_Angles = atan2(Input::Horizotal(), -Input::Vertical());

	m_UnitModel.angles = m_Angles;
}
/*
*   ����
*/
void CPlayer::Weapon()
{
}

void CPlayer::Collision()
{
}
