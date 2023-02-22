#include "game_camera.h"
#include "../../unit_manager/unit/player/player.h"
#include "../../input/input.h"
#include "../../common_data/common_data.h"
const aqua::CVector3 CGameCamera::m_camera_position = aqua::CVector3(0, 75, 25);

/*
 *  �R���X�g���N�^
 */
CGameCamera::CGameCamera(aqua::IGameObject* parent)
	:ICamera(parent, "GameCamera")
{
}
/*
 *  ������
 */
void CGameCamera::Initialize()
{
	m_PlayerClass = (CPlayer*)aqua::FindGameObject("Player");
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);

	if (m_PlayerClass)
	{
		m_Camera.camera_position = m_PlayerClass->GetPosition() + m_camera_position;
		m_Camera.target_point = m_PlayerClass->GetPosition();
	}

	m_Range_of_VisionSprite.Create("data\\game_graph\\���E_2.png");

}
/*
 *  �X�V
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
 *  �`��
 */
void CGameCamera::Draw()
{
	ICamera::Draw();

	m_Range_of_VisionSprite.Draw();
}
/*
* ���
*/
void CGameCamera::Finalize()
{
	m_Range_of_VisionSprite.Delete();
	ICamera::Finalize();
}
