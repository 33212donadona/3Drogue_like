#include "select_camera.h"
#include "../../select_back_ground/select_back_ground.h"
#include "../../scene_manager/scene/2_select/select_system/select_system.h"
const aqua::CVector3 CSelsectCamera::m_camera_position = aqua::CVector3(0, 40, 25);

/*
 *  コンストラクタ
 */
CSelsectCamera::CSelsectCamera(aqua::IGameObject* parent)
	:ICamera(parent, "SelectCamera")
{
}
/*
 *  初期化
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
 *  更新
 */
void CSelsectCamera::Update()
{
	// カメラの中心を設定
	m_Camera.target_point = m_System->GetTargetPosition();
	// カメラの位置更新
	m_Camera.camera_position.x = m_camera_position.x + m_System->GetTargetPosition().x;
	m_Camera.camera_position.z = m_camera_position.z + m_System->GetTargetPosition().z;

	ICamera::Update();
}
/*
 *  描画
 */
void CSelsectCamera::Draw()
{
	ICamera::Draw();
}

void CSelsectCamera::Finalize()
{
	ICamera::Finalize();
}
