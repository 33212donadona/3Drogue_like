#include "job_manager.h"

CJobManager::CJobManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"JobManager")
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