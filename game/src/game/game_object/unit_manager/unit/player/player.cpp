#include "player.h"
#include "../../../job_manager/job_manager.h"
#include "../../../bag/bag_data.h"
#include "../../../weapon_manager/weapon_manager.h"
#include "../../../weapon_manager/weapon/weapon_id.h"
#include "../../../common_data/common_data.h"
#include "../enemy/enemy.h"
#include "../../../stage/stage.h"
#include "../../../input/input.h"

const float CPlayer::m_shot_animetion_frame = 50.0f;
const float CPlayer::m_chage_max_time = 1.8f;
const float CPlayer::m_max_hit_point = 50.0f;
const float CPlayer::m_attack = 50.0f;

/*
 *  コンストラクタ
 */
CPlayer::CPlayer(aqua::IGameObject* parent)
	:IUnit(parent, "Player")
	, m_Angles(0.0f)
	, m_AttackFlag(false)
	, m_ShotFlag(false)
	, m_Standby(false)
	, m_CancelMagic(false)
	, m_WeaponManager(nullptr)
	, m_JobManager(nullptr)
	, m_CommonData(nullptr)
	, m_AnimeState(P_ANIME_ID::IDLE)
	, m_PlayerJobID(JOB_ID::STUDENT)
{
	for (int sw_i = 0; sw_i < (int)JOB_ID::MAX; sw_i++)
		m_SetingWeapon[sw_i] = (WEAPON_ID)sw_i;
}
/*
 *  初期化
 */
void CPlayer::Initialize()
{
	m_JobManager = aqua::CreateGameObject< CJobManager >(this);

	m_UnitModel.Create("data\\model\\Bot", (int)P_ANIME_ID::MAX);

	m_WeaponManager = (CWeaponManager*)aqua::FindGameObject("WeaponManager");
	m_BagData = (CBagData*)aqua::FindGameObject("BagData");
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	//初期位置設定
	while (m_UnitModel.position == aqua::CVector3::ZERO)
	{
		m_UnitModel.position = m_Stage->GetArePosition(aqua::CPoint(aqua::Rand(21, 1), aqua::Rand(21, 1)));
	}

	m_UnitModel.AttachAnimation((int)m_AnimeState);

	m_WeaponManager->SetHandMatrix(m_UnitModel, "mixamorig:RightHandThumb1");

	m_ChageTime.Setup(m_chage_max_time);



	m_CommonDataInfo = m_CommonData->GetData();
	
	// 職業の初期化
	m_CommonDataInfo.now_job = JOB_ID::TEX_COLLECTOR;//(JOB_ID)aqua::Rand((int)JOB_ID::MAX - 1, 1);
	m_PlayerJobID = m_CommonDataInfo.now_job;
	m_JobManager->SetJobID(m_PlayerJobID);

	// 体力の設定
	m_CommonDataInfo.max_hit_point = m_max_hit_point + m_JobManager->GetJobHitPointState();
	m_HitPoint = m_CommonDataInfo.hit_point;

	m_CommonData->SetData(m_CommonDataInfo);

	// バックの中身の登録
	//m_BagData->SetWeapon(0, WEAPON_ID::MONEY, 50, 30);

	m_WeaponManager->SetWeapon(m_SetingWeapon[(int)m_PlayerJobID]);

	m_Attack = m_JobManager->GetJobAttackState() + m_BagData->GetWeaponData(m_BagData->GetSelectBagNumber()).attack;

	IUnit::Initialize();
}

/*
 *  更新
 */
void CPlayer::Update()
{
	Weapon();

	m_CommonDataInfo = m_CommonData->GetData();

	m_CommonDataInfo.hit_point = m_HitPoint;

	m_CommonData->SetData(m_CommonDataInfo);

	IUnit::Update();

	m_UnitModel.AttachAnimation((int)m_AnimeState);
}
/*
 *  解放
 */
void CPlayer::Finalize()
{
	m_CommonDataInfo.hit_point = m_HitPoint;

	m_CommonData->SetData(m_CommonDataInfo);

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
	return (int)m_AnimeState;
}

bool CPlayer::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_WeaponManager->CheckHit(first_pos, end_pos) && m_AttackFlag;
}

float CPlayer::GetAngle()
{
	return m_UnitModel.angles;
}

bool CPlayer::GetAttackFlag()
{
	return m_AttackFlag;
}

bool CPlayer::GetStandbyFlag()
{
	return m_Standby;
}

bool CPlayer::GetShotFlag()
{
	return m_ShotFlag;
}

bool CPlayer::GetCancelMagic()
{
	return m_CancelMagic;
}

void CPlayer::SetJodID(JOB_ID job_id)
{
	CommonDataInfo info = m_CommonData->GetData( );

	info.now_job = job_id;

	m_PlayerJobID = job_id;

	m_JobManager->SetJobID(job_id);
	m_CommonData->SetData(info);
}

JOB_ID CPlayer::GetPlayerJob()
{
	return m_PlayerJobID;
}

/*
 *  アニメーションの更新
 */
void CPlayer::AnimetionWork()
{
	switch (m_SetingWeapon[(int)m_PlayerJobID])
	{
	case WEAPON_ID::FIST:
		FistAnimeWork();
		break;
	case WEAPON_ID::SWORD:
		SwordAnimeWork();
		break;
	case WEAPON_ID::MAGIC:
		MagicAnimeWork();
		break;
	case WEAPON_ID::MONEY:
		MoneyAnimeWork();
		break;
	case WEAPON_ID::MAX:
		break;
	default:
		break;
	}
}
/*
*  素手の時のアニメーション
*/
void CPlayer::FistAnimeWork()
{
	if (!m_AttackFlag)
	{
		if (Input::Horizotal() || Input::Vertical())
			m_AnimeState = P_ANIME_ID::RUN;
		else
			m_AnimeState = P_ANIME_ID::IDLE;
	}

	if (Input::In(Input::KEY_ID::B))
	{
		m_AttackFlag = true;
		m_AnimeState = P_ANIME_ID::SLASH;
	}

	if (m_UnitModel.AnimetionFinished() && m_AnimeState == P_ANIME_ID::SLASH)
		m_AttackFlag = false;
}
/*
*  剣の時のアニメーション
*/
void CPlayer::SwordAnimeWork()
{
	if (Input::In(Input::KEY_ID::B) && !m_AttackFlag)
	{

		m_AnimeState = P_ANIME_ID::SLASH;
		m_AttackFlag = true;
	}

	if (m_AttackFlag && m_UnitModel.AnimetionFinished(60.0f))
	{
		m_AttackFlag = false;
	}

	if (!m_AttackFlag)
	{
		if (Input::Horizotal() || Input::Vertical())
			m_AnimeState = P_ANIME_ID::RUN;
		else
			m_AnimeState = P_ANIME_ID::IDLE;
	}

}
/*
*  魔法の時のアニメーション
*/
void CPlayer::MagicAnimeWork()
{
	if (!m_AttackFlag && m_AnimeState != P_ANIME_ID::MAGIC_SHOT)
	{
		if (Input::Horizotal() || Input::Vertical())
		{
			if (m_Standby)
				m_AnimeState = P_ANIME_ID::MAGIC_RUN;
			else
				m_AnimeState = P_ANIME_ID::RUN;
		}
		else
		{
			if (m_Standby)
				m_AnimeState = P_ANIME_ID::MAGIC_IDLE;
			else
				m_AnimeState = P_ANIME_ID::IDLE;

		}
	}

	if (Input::In(Input::KEY_ID::B))
	{
		m_Standby = true;
	}

	if (m_Standby)
		m_ChageTime.Update();

	if (m_CancelMagic)
		m_CancelMagic = false;

	if (Input::Out(Input::KEY_ID::B))
	{
		if (m_ChageTime.Finished())
		{
			m_AnimeState = P_ANIME_ID::MAGIC_SHOT;
		}
		else
			m_CancelMagic = true;

		m_ChageTime.Reset();
		m_Standby = false;
	}

	if (m_ChageTime.Finished())
		m_ShotFlag = true;

	if (m_AnimeState == P_ANIME_ID::MAGIC_SHOT)
	{
		if (m_UnitModel.AnimetionFinished(54.0f))
		{
			m_AttackFlag = true;
		}

		if (m_UnitModel.AnimetionFinished(80.0f) && m_AttackFlag)
		{
			m_AttackFlag = false;
			m_ShotFlag = false;
			m_AnimeState = P_ANIME_ID::IDLE;
		}
	}
}
/*
*  お金の武器の時のアニメーション
*/
void CPlayer::MoneyAnimeWork()
{
	if (!m_AttackFlag && m_AnimeState != P_ANIME_ID::MONEY_SHOT)
	{
		if (Input::Horizotal() || Input::Vertical())
			m_AnimeState = P_ANIME_ID::RUN;
		else
			m_AnimeState = P_ANIME_ID::IDLE;
	}

	if (Input::In(Input::KEY_ID::B))
	{
		m_AnimeState = P_ANIME_ID::MONEY_SHOT;
		m_BagData->AddToDepositBalance(-100);
	}
	if (m_AnimeState == P_ANIME_ID::MONEY_SHOT && m_UnitModel.AnimetionFinished(30.0f))
	{
		m_ShotFlag = true;
		m_AttackFlag = true;
	}
	if (m_AnimeState == P_ANIME_ID::MONEY_SHOT && m_UnitModel.AnimetionFinished(30.0f + 2.0f))
		m_ShotFlag = false;
	if (m_AnimeState == P_ANIME_ID::MONEY_SHOT && m_UnitModel.AnimetionFinished(30.0f + 10.0f))
	{
		m_AttackFlag = false;
	}
	if (m_AnimeState == P_ANIME_ID::MONEY_SHOT && m_UnitModel.AnimetionFinished())
	{
		m_AnimeState = P_ANIME_ID::IDLE;
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

	if (m_AttackFlag || m_AnimeState == P_ANIME_ID::MAGIC_SHOT || m_AnimeState == P_ANIME_ID::MONEY_SHOT)
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
	if (!m_AttackFlag && m_AnimeState != P_ANIME_ID::MAGIC_SHOT && m_AnimeState != P_ANIME_ID::MONEY_SHOT)
		if (Input::Horizotal() || Input::Vertical())
			m_Angles = atan2(Input::Horizotal(), -Input::Vertical());

	m_UnitModel.angles = m_Angles;
}

/*
*   武器
*/
void CPlayer::Weapon()
{
	//if (Input::In(Input::KEY_ID::B) && m_BagData->GetBagFlag())
	//	if (m_WeaponManager)
	//	{
	//		m_WeaponManager->SetWeapon(m_BagData->GetWeaponData(m_BagData->GetSelectBagNumber()).id);
	//	}

	m_WeaponManager->SetHandMatrix(m_UnitModel, "mixamorig:RightHandThumb1");
}