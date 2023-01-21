#pragma once

#include "aqua.h"

enum class SCENE_ID
{
	TITLE,
	SELECT,
	GAMEMAIN,
	RESULT,

	DUMMY,
};

class CGameSoundManager;

class IScene : public aqua::IGameObject
{
public:
	IScene(aqua::IGameObject* parent, const std::string& name);

	~IScene() override = default;

	void Draw(void)	override;
protected:
	aqua::CLabel m_Label;
	CGameSoundManager* m_SoundManager;
};
