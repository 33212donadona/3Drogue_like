#include "unit.h"
#include "../enemy/enemy.h"

const int CUnit::m_max_animetion = 6;
const float CUnit::m_shot_animetion_frame = 50.0f;
const float CUnit::m_max_hit_point = 50.0f;
const float CUnit::m_attack = 50.0f;

/*
 *  コンストラクタ
 */
CUnit::CUnit(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Unit")
	, m_Angles(0.0f)
	, m_ShotMagic(false)
	, m_Weapon(nullptr)
	, m_Magic(nullptr)
{
}
/*
 *  初期化
 */
void CUnit::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", m_max_animetion);

	m_UnitModel.scale = aqua::CVector3::ONE * 0.1f;

	Animetion = 0;

	m_Weapon = (IWeapon*)aqua::CreateGameObject<CSword>(this);
	m_Magic = (IMagic*)aqua::CreateGameObject<CFireBall>(this);
	m_UnitModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
	if (m_Weapon)m_Weapon->Initialize();
	if (m_Magic)m_Magic->Initialize();

	m_Enemy = (CEnemy*)aqua::FindGameObject("Enemy");
}

/*
 *  更新
 */
void CUnit::Update()
{
	AnimetionWork();

	Move();

	Rotation();

	Weapon();

	m_UnitModel.AnimationUpdata();
}
/*
 *  描画
 */
void CUnit::Draw()
{
	IGameObject::Draw();
}
/*
 *  解放
 */
void CUnit::Finalize()
{
	m_UnitModel.Delete();
	if (m_Weapon)m_Weapon->Finalize();
	if (m_Magic)m_Magic->Finalize();
}
/*
 *  アニメーション番号
 */
int CUnit::GetAnimetionNum()
{
	return Animetion;
}
/*
 *  座標取得
 */
aqua::CVector3 CUnit::GetPosition()
{
	return m_UnitModel.position;
}
/*
 *  アニメーションの更新
 */
void CUnit::AnimetionWork()
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
*   移動
*/
void CUnit::Move()
{
	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::D);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::W);

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x, -95.0f, 95.0f);
	m_UnitModel.position.y = aqua::Limit(m_UnitModel.position.y, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z, -95.0f, 95.0f);
}
/*
*   回転
*/
void CUnit::Rotation()
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

	m_UnitModel.angles.x = aqua::DegToRad(m_Angles);
}
/*
*   武器
*/
void CUnit::Weapon()
{
	if (m_Weapon)m_Weapon->SetMatrix(m_UnitModel.GetBoneMatrix(42));

	if (m_Weapon)m_Weapon->Update();

	aqua::CVector3 pos = m_UnitModel.GetBonePosistion(40);

	if (m_ShotMagic)
	{
		m_MagicFrame += 2;
		pos -= aqua::CVector3(sin(aqua::DegToRad(m_Angles)), 0.0f, cos(aqua::DegToRad(m_Angles))) * (float)m_MagicFrame;
		
		if (m_Enemy)
			m_Enemy->Damage(0, pos, pos);//TODO
	}
	else
		m_MagicFrame = 0;

	if (m_MagicFrame >= 100)
		m_ShotMagic = false;

	if (m_Magic)
	{
		m_Magic->SetPosition(pos);
		m_Magic->Update();
	}
}

void CUnit::Collision()
{
}
