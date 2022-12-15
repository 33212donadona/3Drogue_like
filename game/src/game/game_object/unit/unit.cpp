#include "unit.h"

CUnit::CUnit(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Unit")
{
}

void CUnit::Initialize()
{
	m_UnitModel.Create("data\\zero");
}

void CUnit::Update()
{
	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::D)  - aqua::keyboard::Button(aqua::keyboard::KEY_ID::A);
	m_UnitModel.position.y += aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::W)  - aqua::keyboard::Button(aqua::keyboard::KEY_ID::S);
}

void CUnit::Draw()
{

	IGameObject::Draw();
}

void CUnit::Finalize()
{
	m_UnitModel.Delete();
}
