#include "enemy.h"
#include "../unit/unit.h"

/*
 *  �R���X�g���N�^
 */
CEnemy::CEnemy(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Enemy")
{
}
/*
 *  ������
 */
void CEnemy::Initialize()
{
	m_UnitModel = (CUnit*)aqua::FindGameObject("Unit");

	m_EnemyModel.Create("data\\model\\Enemy",4);
	m_EnemyModel.scale = aqua::CVector3::ONE * 0.1f;
	m_EnemyModel.position = aqua::CVector3(0.0f, 0.0f, 75.0f);
	m_EnemyModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
}
/*
 *  �X�V
 */
void CEnemy::Update()
{
	aqua::CVector3 angle = m_EnemyModel.position - m_UnitModel->GetPosition();
	m_EnemyModel.angles.x = atan2(angle.x, angle.z);
	m_EnemyModel.AnimationUpdata();
}
/*
 *  ���
 */
void CEnemy::Finalize()
{
	m_EnemyModel.Delete();
}