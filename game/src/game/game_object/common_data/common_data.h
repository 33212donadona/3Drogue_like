#pragma once
#include "aqua.h"
#include "common_data_info.h"

class CCommonData :
	public aqua::IGameObject
{
public:

	CCommonData(aqua::IGameObject* parent);
	~CCommonData() = default;

	void SetData(CommonDataInfo common_data);
	void SetData(int max_stage,int crea_stage);
	CommonDataInfo GetData();

private:
	CommonDataInfo m_MapData;
};