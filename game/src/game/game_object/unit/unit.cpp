#include "unit.h"

const int CUnit::m_max_animetion = 6;

/*
 *  コンストラクタ
 */
CUnit::CUnit(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Unit")
	, m_Angles(0.0f)
	, m_Weapon(nullptr)
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

	//m_Weapon = (IWeapon*)aqua::CreateGameObject<CMagicStick>(this);
	m_UnitModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
	if(m_Weapon)m_Weapon->Initialize();
}

/*
 *  更新
 */
void CUnit::Update()
{
	AnimetionWork();

	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::D);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::W);

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x, -95.0f, 95.0f);
	m_UnitModel.position.y = aqua::Limit(m_UnitModel.position.y, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z, -95.0f, 95.0f);

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

	m_UnitModel.AnimationUpdata();

	if (m_Weapon)m_Weapon->SetMatrix(m_UnitModel.GetBoneMatrix(42));

	if (m_Weapon)m_Weapon->Update();
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
		Animetion = 5;
	else
		Animetion = 0;

	m_UnitModel.AttachAnimation(Animetion);
}