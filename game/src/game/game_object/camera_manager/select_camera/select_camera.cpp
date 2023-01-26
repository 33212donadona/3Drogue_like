#include "select_camera.h"
#include "../../select_back_ground/select_back_ground.h"
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
	ICamera::Update();
}
/*
 *  描画
 */
void CSelsectCamera::Draw()
{
	ICamera::Draw();

#ifdef AQUA_DEBUG

#endif

}

void CSelsectCamera::Finalize()
{
	m_Camera.Delete();
}
