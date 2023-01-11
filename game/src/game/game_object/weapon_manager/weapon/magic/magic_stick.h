#pragma once
#include "../weapon.h"

class CMagicStick : public IWeapon
{
public:
	CMagicStick(aqua::IGameObject* parent);
	~CMagicStick() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;
};

