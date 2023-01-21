#include "unit.h"

IUnit::IUnit(aqua::IGameObject* parent,std::string name)
	:aqua::IGameObject(parent,name,"Unit")
	, m_MaxAnimetion(0)
{
}
/*
*  ‰Šú‰»
*/
void IUnit::Initialize()
{
	m_UnitModel.scale = aqua::CVector3::ONE * 0.1f;
	m_UnitModel.axis.y = 1.0f;
	m_HitPoint = m_MaxHitPoint;

	IGameObject::Initialize();
}

/*
*  XV
*/
void IUnit::Update()
{
	m_UnitModel.AnimationUpdata();
	IGameObject::Update();
}

/*
*  ‰ğ•ú
*/
void IUnit::Finalize()
{
	m_UnitModel.Delete();
	IGameObject::Finalize();
}

/*
*  UŒ‚—Í‚Ìæ“¾
*/
float IUnit::GetAttack()
{
	return m_Attack;
}
/*
 *  À•Wæ“¾
 */
aqua::CVector3 IUnit::GetPosition()
{
	return m_UnitModel.position;
}
