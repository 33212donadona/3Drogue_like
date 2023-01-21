#pragma once

#include "../../scene_manager.h"

class CTitle : public IScene
{
public:
	CTitle			(aqua::IGameObject* parent);

	~CTitle			(void) = default;

	void Initialize	(void)	override;

	void Update		(void)	override;

	void Draw		(void)	override;

	void Finalize	(void)	override;

private:
	aqua::CSprite m_TitleSprite;

	aqua::CSprite m_TitleSpriteAdd;

	aqua::CSprite m_CinemaSpriteUp;
	aqua::CSprite m_CinemaSpriteUpSecond;
	
	aqua::CSprite m_CinemaSpriteDown;
	aqua::CSprite m_CinemaSpriteDownSecond;

	aqua::CSprite m_WhiteSprite;

	aqua::CSprite m_DesignBox;
	aqua::CSprite m_DesignBoxUp;
	aqua::CSprite m_DesignBoxDown;
	aqua::CSprite m_TeamNameSpeite;

	aqua::CSprite m_PushMassage;

	aqua::CTimer m_TitleStartTimer;
	aqua::CTimer m_EasingTimer;
};