#pragma once

#include "../../scene_manager.h"

class CGameMain : public IScene
{
public:

	CGameMain(IGameObject* parent);
	~CGameMain() = default;

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Finalize()		override;
};