#include "select_camera.h"
#include "../../select_back_ground/select_back_ground.h"
#include "../../scene_manager/scene/2_select/select_system/select_system.h"
const aqua::CVector3 CSelsectCamera::m_camera_position = aqua::CVector3(0, 40, 25);

/*
 *  �R���X�g���N�^
 */
CSelsectCamera::CSelsectCamera(aqua::IGameObject* parent)
	:ICamera(parent, "SelectCamera")
{
}
/*
 *  ������
 */
void CSelsectCamera::Initialize()
{
	m_BackGround = (CSelectBackGround*)aqua::FindGameObject("SelectBackGround");
	m_System = (CSelectSystem*)aqua::FindGameObject("SelectSystem");

	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	m_Camera.camera_position = m_camera_position;
	m_Camera.m_BackGraph.Create(m_BackGround->GetBackGround());

	m_StageTargetLabel.Create(150);
	m_StageTargetLabel.text = "�ڕW�X�e�[�W�� : " + std::to_string(10);
	m_StageTargetLabel.position = aqua::GetWindowSize() / 2;
	m_StageTargetLabel.position.x -= m_StageTargetLabel.GetTextWidth() / 2.0f;
	m_StageTargetLabel.position.y = 50.0f;
	m_StageTargetLabel.color = aqua::CColor::GREEN;
	ICamera::Initialize();
}
/*
 *  �X�V
 */
void CSelsectCamera::Update()
{
	// �J�����̒��S��ݒ�
	m_Camera.target_point = m_System->GetTargetPosition();
	// �J�����̈ʒu�X�V
	m_Camera.camera_position.x = m_camera_position.x + m_System->GetTargetPosition().x;
	m_Camera.camera_position.z = m_camera_position.z + m_System->GetTargetPosition().z;

	if (m_System->GetPrevLavel() != m_System->GetNowLavel())
		m_StageTargetLabel.text = "�ڕW�X�e�[�W�� : " + std::to_string((m_System->GetNowLavel() + 1) * 10);

	ICamera::Update();
}
/*
 *  �`��
 */
void CSelsectCamera::Draw()
{
	ICamera::Draw();
	m_StageTargetLabel.Draw();
}
/*
* ���
*/
void CSelsectCamera::Finalize()
{
	m_StageTargetLabel.Delete();
	ICamera::Finalize();
}
