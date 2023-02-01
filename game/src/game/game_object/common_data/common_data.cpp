#include "common_data.h"

const int CCommonData::m_selct_max_crea_target = 3;

CCommonData::CCommonData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CommonData")
{
	m_MapData.crea_target = 10;
	m_MapData.crea_stage = 0;
	m_MapData.easy = 0;
	m_MapData.normal = 0;
	m_MapData.hard = 0;
	m_MapData.game_crea_time = 0.0f;
}

void CCommonData::SetData(CommonDataInfo common_data)
{
	m_MapData.crea_target = common_data.crea_target;
	m_MapData.crea_stage = common_data.crea_stage;
	m_MapData.easy = common_data.easy;
	m_MapData.normal = common_data.normal;
	m_MapData.hard = common_data.hard;
	m_MapData.game_crea_time = common_data.game_crea_time;

}

void CCommonData::SetData(int max_stage, int crea_stage, int easy, int normal, int hard, float game_crea_time)
{
	if (m_MapData.crea_target != max_stage)
		m_MapData.crea_target = max_stage;

	if (m_MapData.crea_stage != crea_stage)
		m_MapData.crea_stage = crea_stage;

	if (m_MapData.easy != easy)
		m_MapData.easy = easy;

	if (m_MapData.normal != normal)
		m_MapData.normal = normal;

	if (m_MapData.hard != hard)
		m_MapData.hard = hard;

	if (m_MapData.game_crea_time != game_crea_time)
		m_MapData.game_crea_time = game_crea_time;
}

CommonDataInfo CCommonData::GetData()
{
	return m_MapData;
}

int CCommonData::GetSelectMaxCreaTarget()
{
	return m_selct_max_crea_target;
}
