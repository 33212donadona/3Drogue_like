#pragma once
#include "../object.h"
class CObjectRock : public IObject
{
public:
	CObjectRock(aqua::IGameObject* parent);
	~CObjectRock() = default;

	void Initialize(aqua::CVector3 position)override;
	void Update() override;
	void Finalize() override;
};

