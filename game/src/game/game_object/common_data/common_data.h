#pragma once
#include "aqua.h"

struct CommonData
{
	int max_map_data;
};

class CCommonData :
	public aqua::IGameObject
{
public:

	CCommonData(aqua::IGameObject* parent);
	~CCommonData() = default;

	void SetData(CommonData common_data);
	CommonData GetData();

private:
	CommonData m_MapData;
};