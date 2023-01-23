#include "game_camera.h"
#include "../unit_manager/unit/player/player.h"
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
	m_PlayerClass = (CPlayer*)aqua::FindGameObject("Player");
	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	if (m_PlayerClass)
	{
		m_Camera.camera_position = m_PlayerClass->GetPosition() + m_camera_position;
		m_Camera.target_point = m_PlayerClass->GetPosition();
	}
}
/*
 *  更新
 */
void CGameCamera::Update()
{
	if (m_PlayerClass)
	{
		m_Camera.camera_position = m_PlayerClass->GetPosition() + m_camera_position;
		m_Camera.target_point = m_PlayerClass->GetPosition();
	}
}
/*
 *  描画
 */
void CGameCamera::Draw()
{
	m_Camera.Draw();

#ifdef DEBUG

	aqua::CLabel cl;
	cl.Create(20);
	cl.color = aqua::CColor::BLUE;
	cl.text = std::to_string(m_PlayerClass->GetAnimetionNum()) + "\n" +
		"x:" + std::to_string(m_Camera.camera_position.x) + "\n"
		"y:" + std::to_string(m_Camera.camera_position.y) + "\n"
		"z:" + std::to_string(m_Camera.camera_position.z) + "\n";

	cl.Draw();
	cl.Delete();
#endif

}
