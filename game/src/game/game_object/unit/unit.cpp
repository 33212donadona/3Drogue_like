#include "unit.h"

const int CUnit::m_max_animetion = 4;

/*
 *  コンストラクタ
 */
CUnit::CUnit(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Unit")
	, m_Angles(0.0f)
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

	m_W = (IWeapon*)aqua::CreateGameObject<CSword>(this);
	m_W->m_ModelScale = aqua::CVector3::ONE * 0.005f;
	m_UnitModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
	m_W->Initialize();
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
		m_Angles = Horizotal * 45;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S))
		m_Angles = 180 - Horizotal * 45;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		m_Angles = 270;
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		m_Angles = 90;

	m_UnitModel.angles.x = aqua::DegToRad(m_Angles);

	m_UnitModel.AnimationUpdata();

	m_W->m_ModelPosition = m_UnitModel.GetBonePosistion(11);
	m_W->m_ModelMatrix = m_UnitModel.GetBoneMatrix(11);

	m_W->Update();
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
	m_W->Finalize();
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
	else
		Animetion = 0;

	m_UnitModel.AttachAnimation(Animetion);
}