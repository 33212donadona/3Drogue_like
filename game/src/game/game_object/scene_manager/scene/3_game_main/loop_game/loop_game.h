#pragma once
#include "aqua.h"
#include "../../../../common_data/common_data_info.h"
#include "../../../../stage/stage_id.h"

class CUnitManager;
class CCommonData;

enum class LOOP_STATE
{
	FADE_IN,
	UPDATA,
	FADE_OUT,
	SELECT_LEVER,

	MAX
};

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

	void SelectNextStageLaver();

private:
	static const float m_fade_max_time;
	static const std::string m_lever_file_name[(int)STAGE_LEVER::MAX];

	CUnitManager*    m_UnitManager;
	CCommonData*     m_CommonData;
	CommonDataInfo   m_GameData;
	LOOP_STATE       m_LoopState;
	aqua::CBoxPrimitive m_FadeBox;
	aqua::CTimer        m_FadeTimer;
	aqua::CLabel        m_SelectLabel;
	aqua::CSprite*      m_LeverSprite;

	int                 m_NextLever[2];

	bool m_SelectNextStageFlag;

};