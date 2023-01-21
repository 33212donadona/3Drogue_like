#include "common_data.h"

CCommonData::CCommonData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"CommonData")
{
	m_MapData.max_map_data = 10;
}

void CCommonData::SetData(CommonData common_data)
{
	m_MapData = common_data;
}

CommonData CCommonData::GetData()
{
	return m_MapData;

}
