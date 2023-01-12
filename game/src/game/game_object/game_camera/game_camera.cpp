#include "game_camera.h"
#include "../unit/unit.h"
const aqua::CVector3 CGameCamera::m_camera_position = aqua::CVector3(0, 75, 25);

/*
 *  コンストラクタ
 */
CGameCamera::CGameCamera(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "GameCamera")
{
}
/*
 *  初期化
 */
void CGameCamera::Initialize()
{
	m_UnitClass = (CUnit*)aqua::FindGameObject("Unit");
	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	if (m_UnitClass)
	{
		m_Camera.camera_position = m_UnitClass->GetPosition() + m_camera_position;
		m_Camera.target_point = m_UnitClass->GetPosition();
	}
}
/*
 *  更新
 */
void CGameCamera::Update()
{
	if (m_UnitClass)
	{
		//m_Camera.camera_position = m_UnitClass->m_UnitModel.position + aqua::CVector3(0, 50, 50);
		//m_Camera.target_point = m_UnitClass->m_UnitModel.position;
		m_Camera.camera_position = m_UnitClass->GetPosition() + m_camera_position;
		m_Camera.target_point = m_UnitClass->GetPosition();
	}
}
/*
 *  描画
 */
void CGameCamera::Draw()
{
	m_Camera.Draw();

	aqua::CLabel cl;
	cl.Create(20);
	cl.color = aqua::CColor::BLUE;
	cl.text = std::to_string(m_UnitClass->GetAnimetionNum()) + "\n" +
		"x:" + std::to_string(m_Camera.camera_position.x) + "\n"
		"y:" + std::to_string(m_Camera.camera_position.y) + "\n"
		"z:" + std::to_string(m_Camera.camera_position.z) + "\n";

	//cl.Draw();
	cl.Delete();
}
