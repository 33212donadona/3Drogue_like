#include "job_manager.h"
const float CJobManager::m_JobAttackState[] =
{
	30.0f,
	45.0f,
	67.5f,
	34.5f
};
const float CJobManager::m_JobHitPointState[] =
{
	200.0f,
	240.0f,
	160.0f,
	200.0f
};

CJobManager::CJobManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "JobManager")
{
}
/*
* �E�Ƃ̐ݒ�
*/
void CJobManager::SetJobID(JOB_ID job_id)
{
	m_JobID = JOB_ID((int)job_id % (int)JOB_ID::MAX);
}
/*
* �E�Ƃ̎擾
*/
JOB_ID CJobManager::GetJobID()
{
	return m_JobID;
}
/*
* �E�Ƃ̍U����
*/
float CJobManager::GetJobAttackState()
{
	return m_JobAttackState[(int)m_JobID];
}
/*
* �E�Ƃ̗̑�
*/
float CJobManager::GetJobHitPointState()
{
	return m_JobHitPointState[(int)m_JobID];
}
