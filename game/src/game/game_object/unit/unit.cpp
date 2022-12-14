#include "unit.h"

CUnit::CUnit(aqua::IGameObject* parent)
{
}

void CUnit::Initialize()
{
	m_UnitModel.Create("data\\zero");
	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	m_Camera.camera_position = m_UnitModel.position - aqua::CVector3(50,0,50);
}

void CUnit::Update()
{
	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::D)  - aqua::keyboard::Button(aqua::keyboard::KEY_ID::A);
	m_UnitModel.position.y += aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::W)  - aqua::keyboard::Button(aqua::keyboard::KEY_ID::S);
}

void CUnit::Draw()
{
	m_Camera.Draw();
	IGameObject::Draw();
}

void CUnit::Finalize()
{
	m_UnitModel.Delete();
}
