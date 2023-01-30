#include "common_data.h"

CCommonData::CCommonData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CommonData")
{
	m_MapData.max_stage = 10;
	m_MapData.crea_stage = 0;
}

void CCommonData::SetData(CommonDataInfo common_data)
{
	m_MapData.max_stage  = common_data.max_stage;
	m_MapData.crea_stage = common_data.crea_stage;
}

void CCommonData::SetData(int max_stage, int crea_stage)
{
	if (m_MapData.max_stage != max_stage)
		m_MapData.max_stage = max_stage;

	if (m_MapData.crea_stage != crea_stage)
		m_MapData.crea_stage = crea_stage;
}

CommonDataInfo CCommonData::GetData()
{
	return m_MapData;
}
