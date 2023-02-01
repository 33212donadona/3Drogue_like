#include "player.h"
#include "../../../weapon_manager/weapon_manager.h"
#include "../../../weapon_manager/weapon/weapon_id.h"
#include "../enemy/enemy.h"
#include "../../../stage/stage.h"
#include "../../../input/input.h"

const int CPlayer::m_max_animetion = 6;
const float CPlayer::m_shot_animetion_frame = 50.0f;
const float CPlayer::m_max_hit_point = 50.0f;
const float CPlayer::m_attack = 50.0f;

/*
 *  コンストラクタ
 */
CPlayer::CPlayer(aqua::IGameObject* parent)
	:IUnit(parent, "Player")
	, m_Angles(0.0f)
	, m_Attack(false)
	, m_ShotMagic(false)
	, m_WeaponManager(nullptr)
{
}
/*
 *  初期化
 */
void CPlayer::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", m_max_animetion);

	m_WeaponManager = (CWeaponManager*)aqua::FindGameObject("WeaponManager");

	Animetion = 0;

	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	//初期位置設定
	while (m_UnitModel.position == aqua::CVector3::ZERO)
	{
		m_UnitModel.position = m_Stage->GetArePosition(aqua::CPoint(aqua::Rand(21, 1), aqua::Rand(21, 1)));
	}

	m_UnitModel.AttachAnimation(Animetion);

	if (m_WeaponManager)
	{
		m_WeaponManager->SetWeapon(WEAPON_ID::SWORD);
		m_WeaponManager->SetHandMatrix(m_UnitModel, "mixamorig:RightHandThumb1");
	}

	m_HitPoint = 100;

	IUnit::Initialize();
}

/*
 *  更新
 */
void CPlayer::Update()
{

	Weapon();

	IUnit::Update();

	m_UnitModel.AttachAnimation(Animetion);
}
/*
 *  解放
 */
void CPlayer::Finalize()
{
	IUnit::Finalize();
}
/*
*  動きの更新
*/
void CPlayer::MoveUpdata()
{
	AnimetionWork();

	Move();

	Rotation();
}
/*
 *  アニメーション番号
 */
int CPlayer::GetAnimetionNum()
{
	return Animetion;
}

bool CPlayer::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_WeaponManager->CheckHit(first_pos, end_pos) && m_Attack;
}

float CPlayer::GetAngle()
{
	return m_Angles;
}

bool CPlayer::GetAttackFlag()
{
	return m_Attack;
}

/*
 *  アニメーションの更新
 */
void CPlayer::AnimetionWork()
{
	if (Input::In(Input::KEY_ID::B) && !m_Attack)
	{
		Animetion = 3;
		m_Attack = true;
	}

	if (!m_Attack)
	{
		if (Input::Horizotal() || Input::Vertical())
			Animetion = 2;
		else
			Animetion = 0;
	}

	if (m_Attack && m_UnitModel.AnimetionFinished(60.0f))
	{
		m_Attack = false;
		Animetion = 0;
	}
}
/*
*   移動
*/
void CPlayer::Move()
{
	float x = -Input::Horizotal();
	float z = Input::Vertical();

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3(x * 4.5f, 0.0f, 0.0f)))
		x = 0.0f;

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3(0.0f, 0.0f, z * 4.5f)))
		z = 0.0f;

	if (m_Attack)
	{
		x = 0.0f;
		z = 0.0f;
	}

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x + x, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z + z, -95.0f, 95.0f);
}

/*
*   回転
*/
void CPlayer::Rotation()
{
	if (!m_Attack)
		if (Input::Horizotal() || Input::Vertical())
			m_Angles = atan2(Input::Horizotal(), -Input::Vertical());

	m_UnitModel.angles = m_Angles;
}
/*
*   武器
*/
void CPlayer::Weapon()
{
	m_WeaponManager->SetHandMatrix(m_UnitModel, "mixamorig:RightHandThumb1");
}

void CPlayer::Collision()
{
}