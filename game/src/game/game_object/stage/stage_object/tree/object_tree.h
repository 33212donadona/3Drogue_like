#pragma once
#include "../object.h"
class CObjectTree : public IObject
{
public:
	CObjectTree(aqua::IGameObject* parent);
	~CObjectTree() = default;

	void Initialize(aqua::CVector3 position)override;
	void Finalize() override;
};