#pragma once
#include "aqua.h"

enum class JOB_ID
{
	STUDENT,
	SWORDMAN,
	WIZARD,
	TEX_COLLECTOR,

	MAX
};

class CJobManager : public aqua::IGameObject
{
public:

	CJobManager(aqua::IGameObject* parent);
	~CJobManager() = default;

	void SetJobID(JOB_ID job_id);

	JOB_ID GetJobID();

	float  GetJobAttackState();
	float  GetJobHitPointState();

private:

	JOB_ID m_JobID;

	static const float m_JobAttackState[(int)JOB_ID::MAX];
	static const float m_JobHitPointState[(int)JOB_ID::MAX];

};
