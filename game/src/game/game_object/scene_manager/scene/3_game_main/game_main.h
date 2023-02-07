#pragma once

#include "../../scene_manager.h"
#include "../../../common_data/common_data_info.h"

class CUnitManager;
class CCommonData;
class CLoopGame;

class CGameMain : public IScene
{
public:

	CGameMain(IGameObject* parent);
	~CGameMain() = default;

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Finalize()		override;

	float GetGameTime(void);

private:
	CUnitManager*     m_UnitManager;
	CLoopGame*        m_LoopGame;
	CCommonData*      m_CommonData;
	CommonDataInfo    m_GameData;
	float             m_Frame;      //! 1秒のフレーム数
	float             m_Timer;      //! 秒数
	aqua::CTimer	  m_GameTimer;
};