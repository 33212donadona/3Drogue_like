#pragma once
#include "../magic.h"
class CFireBall : public IMagic
{
public:
	CFireBall(aqua::IGameObject* parent);
	~CFireBall() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

};

