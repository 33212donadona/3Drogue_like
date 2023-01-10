#include "game_camera.h"
#include "../unit/unit.h"
CGameCamera::CGameCamera(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "GameCamera")
{
}

void CGameCamera::Initialize()
{
	m_UnitClass = (CUnit*)aqua::FindGameObject("Unit");
	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	if (m_UnitClass)
	{
		m_Camera.camera_position = m_UnitClass->m_UnitModel.position + aqua::CVector3(0, 50, 50);
		m_Camera.target_point = m_UnitClass->m_UnitModel.position;
	}
}

void CGameCamera::Update()
{
	if (m_UnitClass)
	{
		//m_Camera.camera_position = m_UnitClass->m_UnitModel.position + aqua::CVector3(0, 50, 50);
		//m_Camera.target_point = m_UnitClass->m_UnitModel.position;
	}
}

void CGameCamera::Draw()
{
	m_Camera.Draw();
}
