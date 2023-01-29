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
	m_System     = (CSelectSystem*)aqua::FindGameObject("SelectSystem");

	m_Camera.Create(aqua::GetWindowSize().x, aqua::GetWindowSize().y);
	m_Camera.camera_position = m_camera_position;
	m_Camera.m_BackGraph.Create(m_BackGround->GetBackGround());

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

	ICamera::Update();
}
/*
 *  �`��
 */
void CSelsectCamera::Draw()
{
	ICamera::Draw();
}

void CSelsectCamera::Finalize()
{
	ICamera::Finalize();
}
