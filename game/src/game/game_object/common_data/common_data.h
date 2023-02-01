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
	void SetData(int max_stage,int crea_stage,int easy,int normal,int hard,float game_crea_time);
	CommonDataInfo GetData();

	int GetSelectMaxCreaTarget();

private:
	static const int m_selct_max_crea_target; //! ‘I‘ð‰Â”\‚È
	CommonDataInfo m_MapData;
};