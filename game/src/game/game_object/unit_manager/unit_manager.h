#pragma once
#include "aqua.h"

class IUnit;

class CUnitManager :public aqua::IGameObject
{
public:

	CUnitManager(aqua::IGameObject* parent);
	~CUnitManager() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

private:
	IUnit* m_Player;
};

