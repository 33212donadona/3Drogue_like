#include "job_icom.h"
#include "../../../common_data/common_data.h"

const std::string CJobIcon::m_icon_file_pass[] =
{
	"data\\game_graph\\Job_Student.png",
	"data\\game_graph\\Job_Knight.png",
	"data\\game_graph\\Job_Wizard.png",
	"data\\game_graph\\Job_TexCollector.png"
};

CJobIcon::CJobIcon(aqua::IGameObject* parent)
	:IUserInterface(parent, "JobIcon")
	, m_CommonData(nullptr)
{
}
/*
* èâä˙âª
*/
void CJobIcon::Initialize()
{
	for (int job_i = 0; job_i < (int)JOB_ID::MAX; job_i++)
	{
		m_JobIconSprite[job_i].Create(m_icon_file_pass[job_i]);
	}

	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
}
/*
* ï`âÊ
*/
void CJobIcon::Draw()
{
	if((int)m_CommonData->GetData().now_job > -1)
	m_JobIconSprite[(int)m_CommonData->GetData( ).now_job].Draw();
}
/*
* âï˙
*/
void CJobIcon::Finalize()
{
	for (int job_i = 0; job_i < (int)JOB_ID::MAX; job_i++)
		m_JobIconSprite[job_i].Delete();
}
