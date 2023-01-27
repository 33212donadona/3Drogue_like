#pragma once

#include "../../scene_manager.h"

class CSelectSystem;

class CSelect : public IScene
{
public:
	CSelect(IGameObject* parent);
	~CSelect() = default;

	void Initialize()	override;
	void Update()		override;
	void Draw()			override;
	void Finalize()		override;

private:
	CSelectSystem* m_SelectSystem;
};

