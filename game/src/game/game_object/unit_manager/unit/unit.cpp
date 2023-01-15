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
	m_HitPoint = m_MaxHitPoint;

	IGameObject::Initialize();
}

/*
*  更新
*/
void IUnit::Update()
{
	m_UnitModel.AnimationUpdata();
	IGameObject::Update();
}

/*
*  解放
*/
void IUnit::Finalize()
{
	m_UnitModel.Delete();
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
