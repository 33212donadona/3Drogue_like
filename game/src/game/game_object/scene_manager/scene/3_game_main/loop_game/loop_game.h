#pragma once
#include "aqua.h"
#include "../../../../common_data/common_data_info.h"

class CUnitManager;

class CCommonData;

class CLoopGame : public aqua::IGameObject
{
public:

	CLoopGame(IGameObject* parent);
	~CLoopGame() = default;

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Finalize()		override;

	bool ChengeResult();

private:
	CUnitManager*    m_UnitManager;
	CCommonData*     m_CommonData;
	CommonDataInfo   m_GameData;
};