#pragma once
#include "aqua.h"

struct CommonData
{
	const int selct_max_mode = 3;
	int max_stage;//!ゲーム中の最大ステージ数
	int crea_stage;
};

class CCommonData :
	public aqua::IGameObject
{
public:

	CCommonData(aqua::IGameObject* parent);
	~CCommonData() = default;

	void SetData(CommonData common_data);
	void SetData(int max_stage,int crea_stage);
	CommonData GetData();

private:
	CommonData m_MapData;
};