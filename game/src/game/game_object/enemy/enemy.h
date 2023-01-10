#pragma once
#include "aqua.h"

class CUnit;

class CEnemy : public aqua::IGameObject
{
public:
	CEnemy(aqua::IGameObject* parent);
	~CEnemy() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

private:
	aqua::CModel m_EnemyModel;
	CUnit* m_UnitModel;
};