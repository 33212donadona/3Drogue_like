#include "common_data.h"

CCommonData::CCommonData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CommonData")
{
	m_MapData.max_stage = 10;
	m_MapData.crea_stage = 0;
}

void CCommonData::SetData(CommonDataInfo common_data)
{
	m_MapData.max_stage = common_data.max_stage;
	m_MapData.crea_stage = common_data.crea_stage;
	m_MapData.easy = common_data.easy;
	m_MapData.normal = common_data.normal;
	m_MapData.hard = common_data.hard;
	m_MapData.game_crea_time = common_data.game_crea_time;

}

void CCommonData::SetData(int max_stage, int crea_stage, int easy, int normal, int hard, float game_crea_time)
{
	if (m_MapData.max_stage != max_stage)
		m_MapData.max_stage = max_stage;

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
