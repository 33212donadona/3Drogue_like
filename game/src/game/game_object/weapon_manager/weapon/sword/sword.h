#pragma once
#include "../weapon.h"
class CSword :public IWeapon
{
public:
	CSword(aqua::IGameObject* parent);
	~CSword() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;
};

