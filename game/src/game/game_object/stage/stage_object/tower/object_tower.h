#pragma once
#include "../object.h"
class CObjectTower : public IObject
{
public:
	CObjectTower(aqua::IGameObject* parent);
	~CObjectTower() = default;

	void Initialize(aqua::CVector3 position)override;
	void Finalize() override;
};

