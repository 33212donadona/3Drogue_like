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

	int GetAnimetionNum();

	aqua::CVector3 GetPosition();

private:

	void AnimetionWork();

	aqua::CModel m_UnitModel;
	int Animetion;
};