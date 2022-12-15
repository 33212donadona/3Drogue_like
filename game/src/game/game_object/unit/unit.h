#pragma once
#include "aqua.h"

class CUnit : public aqua::IGameObject
{
public:

	CUnit(aqua::IGameObject* parent);
	~CUnit() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

	aqua::CModel m_UnitModel;
private:


};