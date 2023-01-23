#include "player.h"
#include "../enemy/enemy.h"
#include "../../../stage/stage.h"

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
	, m_ShotMagic(false)
	, m_Weapon(nullptr)
	, m_Magic(nullptr)
{
}
/*
 *  初期化
 */
void CPlayer::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", m_max_animetion);

	Animetion = 2;

	m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
	m_Magic = (IMagic*)aqua::CreateGameObject<CFireBall>(this);
	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	//初期位置設定
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
 *  更新
 */
void CPlayer::Update()
{
	AnimetionWork();

	Weapon();

	IUnit::Update();
}
/*
 *  解放
 */
void CPlayer::Finalize()
{
	if (m_Weapon)m_Weapon->Finalize();

	IUnit::Finalize();
}
/*
*  動きの更新
*/
void CPlayer::MoveUpdata()
{
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
	return m_Weapon->CheckHitWeapon(first_pos, end_pos) && aqua::keyboard::Button(aqua::keyboard::KEY_ID::Z);
}

/*
 *  アニメーションの更新
 */
void CPlayer::AnimetionWork()
{
	if (
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::D)
		)
		Animetion = 2;
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
*   移動
*/
void CPlayer::Move()
{
	int x = aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::D);
	int z = aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::W);

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3((float)x * 4.5f, 0.0f, 0.0f)))
		x = 0;

	if (m_Stage->CheckObject(m_UnitModel.position + aqua::CVector3(0.0f, 0.0f, (float)z * 4.5f)))
		z = 0;

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x + x, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z + z, -95.0f, 95.0f);
}

/*
*   回転
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
*   武器
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
