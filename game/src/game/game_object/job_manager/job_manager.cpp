#include "job_manager.h"
const float CJobManager::m_JobAttackState[] =
{
	30.0f,
	45.0f,
	37.5f,
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

void CJobManager::SetJobID(JOB_ID job_id)
{
	m_JobID = JOB_ID((int)job_id % (int)JOB_ID::MAX);
}

JOB_ID CJobManager::GetJobID()
{
	return m_JobID;
}

float CJobManager::GetJobAttackState()
{
	return m_JobHitPointState[(int)m_JobID];
}

float CJobManager::GetJobHitPointState()
{
	return m_JobHitPointState[(int)m_JobID];
}
