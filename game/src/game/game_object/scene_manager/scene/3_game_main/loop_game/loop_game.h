#pragma once
#include "aqua.h"
#include "../../../../common_data/common_data_info.h"
#include "../../../../stage/stage_id.h"

class CUnitManager;
class CCommonData;
class CGameSoundManager;

enum class LOOP_STATE
{
	FADE_IN,
	UPDATA,
	FADE_OUT,
	SELECT_LEVER,
	SELECT_JOB,

	MAX
};

enum class SELECT_BUTTON_SIDE
{
	LEFT,
	RIGHT,

	MAX
};

enum class SELECT_BUTTON_ID
{
	X,
	Y,
	A,
	B,

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

	void SelectNextStageLever();

	void SelectLever();

	void SelectJob();

private:
	static const float m_fade_max_time;
	static const float m_light_max_time;
	static const float m_button_space;
	static const std::string m_lever_file_name[(int)STAGE_LEVER::MAX];
	static const std::string m_lever_light_file_name[(int)STAGE_LEVER::MAX];
	static const std::string m_button_file_name[(int)SELECT_BUTTON_SIDE::MAX];

	CUnitManager*      m_UnitManager;
	CGameSoundManager* m_SoundManager;
	CCommonData*       m_CommonData;
	CommonDataInfo     m_GameData;
	LOOP_STATE         m_LoopState;
	aqua::CBoxPrimitive m_FadeBox;
	aqua::CTimer        m_FadeTimer;
	aqua::CTimer        m_LightTimer;
	aqua::CTimer        m_MaxLightTimer;
	aqua::CLabel        m_SelectLeverLabel;
	aqua::CLabel        m_SelectJobLabel;
	aqua::CLabel        m_SelectJobSubLabel;
	aqua::CSprite       m_LeverSprite[(int)STAGE_LEVER::MAX];
	aqua::CSprite       m_LeverSpriteLight[(int)STAGE_LEVER::MAX];
	aqua::CSprite       m_ButtonSprite[(int)SELECT_BUTTON_SIDE::MAX];

	int                 m_NextLever[(int)SELECT_BUTTON_SIDE::MAX];

	bool m_SelectNextStageFlag;
	bool m_LightFlag;

};