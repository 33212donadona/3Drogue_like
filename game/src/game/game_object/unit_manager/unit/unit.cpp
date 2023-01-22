#include "unit.h"

IUnit::IUnit(aqua::IGameObject* parent,std::string name)
	:aqua::IGameObject(parent,name,"Unit")
	, m_MaxAnimetion(0)
{
}
/*
*  初期化
*/
void IUnit::Initialize()
{
	m_UnitModel.scale = aqua::CVector3::ONE * 0.1f;
	m_UnitModel.axis.y = 1.0f;

	IGameObject::Initialize();
}

/*
*  更新
*/
void IUnit::Update()
{
	m_UnitModel.AnimationUpdata();

	IGameObject::Update();

	if (m_State == STATE::DEAD)
		DeleteObject();

	if (m_HitPoint <= 0)
		m_State = STATE::DEAD;
}

/*
*  解放
*/
void IUnit::Finalize()
{
	m_UnitModel.Delete();
	IGameObject::Finalize();
}

/*
*  攻撃力の取得
*/
float IUnit::GetAttack()
{
	return m_Attack;
}
/*
 *  座標取得
 */
aqua::CVector3 IUnit::GetPosition()
{
	return m_UnitModel.position;
}
