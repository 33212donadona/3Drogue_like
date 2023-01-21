#pragma once

#include "aqua.h"

#include "scene/scene.h"

class CSceneManager : public aqua::IGameObject
{
public:
	CSceneManager		(aqua::IGameObject* parent);

	~CSceneManager		()		override = default;

	void Initialize		(void)	override;

	void Update			(void)	override;

	void Draw			(void)	override;

	void Finalize		(void)	override;

public:
	void ChangeScene	(SCENE_ID id);

private:
	IScene*		m_CurrentScene_P;
	SCENE_ID	m_NextScene;
};