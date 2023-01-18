#include "player.h"
#include "../enemy/enemy.h"

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
	, m_ShotMagic(false)
	, m_Weapon(nullptr)
	, m_Magic(nullptr)
{
}
/*
 *  ������
 */
void CPlayer::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", m_max_animetion);

	Animetion = 0;

	m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
	m_Magic = (IMagic*)aqua::CreateGameObject<CFireBall>(this);
	m_UnitModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
	if (m_Weapon)m_Weapon->Initialize();
	m_MaxHitPoint = 100;

	IUnit::Initialize();
}

/*
 *  �X�V
 */
void CPlayer::Update()
{
	AnimetionWork();

	Move();

	Rotation();

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
 *  �A�j���[�V�����ԍ�
 */
int CPlayer::GetAnimetionNum()
{
	return Animetion;
}

/*
 *  �A�j���[�V�����̍X�V
 */
void CPlayer::AnimetionWork()
{
	if (
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::D)
		)
	{
		Animetion = 2;
	}

	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::Z))
		Animetion = 3;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::X))
		Animetion = 4;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::C))
	{
		Animetion = 5;

		m_ShotMagic = m_UnitModel.AnimetionFinished(m_shot_animetion_frame);
	}
	else
		Animetion = 0;

	m_UnitModel.AttachAnimation(Animetion);
}
/*
*   �ړ�
*/
void CPlayer::Move()
{
	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::D);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::W);

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z, -95.0f, 95.0f);
}
/*
*   ��]
*/
void CPlayer::Rotation()
{
	int Horizotal = aqua::keyboard::Button(aqua::keyboard::KEY_ID::D) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::A);

	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W))
		m_Angles = Horizotal * 45.0f;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S))
		m_Angles = 180 - Horizotal * 45.0f;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		m_Angles = 270.0f;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		m_Angles = 90.0f;

	m_UnitModel.angles = aqua::DegToRad(m_Angles);
}
/*
*   ����
*/
void CPlayer::Weapon()
{
	if (m_Weapon)m_Weapon->SetMatrix(m_UnitModel.GetBoneMatrix(42));

	if (m_Weapon)m_Weapon->Update();

	aqua::CVector3 pos = m_UnitModel.GetBonePosistion(40);

	if (m_ShotMagic)
	{
		m_MagicFrame += 2;
		pos -= aqua::CVector3(sin(aqua::DegToRad(m_Angles)), 0.0f, cos(aqua::DegToRad(m_Angles))) * (float)m_MagicFrame;
	}
	else
		m_MagicFrame = 0;

	if (m_MagicFrame >= 100)
		m_ShotMagic = false;

	if (m_Magic)
	{
		m_Magic->SetPosition(pos);
	}
}

void CPlayer::Collision()
{
}