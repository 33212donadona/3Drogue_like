#include "unit.h"
const float IUnit::m_summon_max_time = 2.0f;
const float IUnit::m_dead_max_time = 2.0f;
const float IUnit::m_first_position_height = -20.0f;
const int IUnit::m_max_dead_effect = 10;

IUnit::IUnit(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent, name, "Unit")
	, m_State(STATE::SUMMON)
	, DeadFlag(false)
	, m_HitPoint(0.0f)
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

	m_DeadEffect = AQUA_NEW aqua::CEffect3D[m_max_dead_effect];

	for (int e_i = 0; e_i < 3; e_i++)
	{
		m_DeadEffect[e_i].Create("data\\effect\\death.efkefc");
		m_DeadEffect[e_i].scale = m_SummonEffect.scale / 2.0f;
	}

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
			for (int e_i = 0; e_i < m_max_dead_effect; e_i++)
			{
				m_DeadEffect[e_i].position = m_UnitModel.position;
				m_DeadEffect[e_i].Play();
			}
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
	m_SummonEffect.Delete();

	if (m_DeadEffect)
		for (int e_i = 0; e_i < m_max_dead_effect; e_i++)
			m_DeadEffect[e_i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_DeadEffect);
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

	if (m_DeadEffect[0].Finished())
	{
		DeleteObject();
		DeadFlag = true;
	}

	for (int e_i = 0; e_i < m_max_dead_effect; e_i++)
		m_DeadEffect[e_i].Update();

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
float IUnit::GetHitPoint()
{
	return m_HitPoint;
}
/*
 *  座標取得
 */
aqua::CVector3 IUnit::GetPosition()
{
	return m_UnitModel.position;
}

bool IUnit::GetDead()
{
	return DeadFlag;
}
