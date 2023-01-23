#include "unit.h"
const float IUnit::m_summon_max_time = 2.0f;
const float IUnit::m_dead_max_time = 2.0f;
const float IUnit::m_first_position_height = -20.0f;

IUnit::IUnit(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent, name, "Unit")
	, m_State(STATE::SUMMON)
{
}
/*
*  初期化
*/
void IUnit::Initialize()
{
	m_UnitModel.scale = aqua::CVector3::ONE * 0.1f;
	m_UnitModel.axis.y = 1.0f;
	m_UnitModel.position.y = m_first_position_height; // 地面の下に設置

	m_EffectTime.Setup(m_summon_max_time);

	m_SummonEffect.Create("data\\effect\\summon.efkefc");
	m_SummonEffect.Play();
	m_SummonEffect.scale = aqua::CVector3::ONE * 10.0f;
	m_SummonEffect.position = m_UnitModel.position;
	m_SummonEffect.position.y = 0.0f;

	m_DeadEffect.Create("data\\effect\\summon.efkefc");
	m_DeadEffect.scale = m_SummonEffect.scale;

	IGameObject::Initialize();
}

/*
*  更新
*/
void IUnit::Update()
{
	switch (m_State)
	{
	case IUnit::STATE::SUMMON:
		Summon();
		break;
	case IUnit::STATE::MOVE:
		
		if (m_EffectTime.Finished())
			m_EffectTime.Reset();

		MoveUpdata();

		if (m_HitPoint <= 0)
		{
			m_State = STATE::DEAD;
			m_DeadEffect.position = m_UnitModel.position;
			m_DeadEffect.Play();
		}
		break;
	case IUnit::STATE::DEAD:
		
		Dead();

		break;
	default:
		break;
	}

	m_UnitModel.AnimationUpdata();

	IGameObject::Update();
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
*  召喚処理
*/
void IUnit::Summon()
{
	m_UnitModel.position.y = aqua::easing::InQuart
	(
		m_EffectTime.GetTime(),
		m_EffectTime.GetLimit(),
		m_first_position_height,
		0.0f
	);

	if (m_SummonEffect.Finished())
		m_State = STATE::MOVE;

	m_SummonEffect.Update();
	m_EffectTime.Update();

	if (m_EffectTime.Finished())
		m_EffectTime.SetTime(m_summon_max_time);
}
/*
*  @brief  死亡処理
*/
void IUnit::Dead()
{
	m_UnitModel.position.y = aqua::easing::OutQuart
	(
		m_EffectTime.GetTime(),
		m_EffectTime.GetLimit(),
		0.0f,
		m_first_position_height
	);

	if (m_DeadEffect.Finished())
		DeleteObject();

	m_DeadEffect.Update();
	m_EffectTime.Update();

	if (m_EffectTime.Finished())
		m_EffectTime.SetTime(m_summon_max_time);
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
