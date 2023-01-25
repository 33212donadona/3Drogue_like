#include "select_camera.h"
#include "../../select_back_ground/select_back_ground.h"
const aqua::CVector3 CSelsectCamera::m_camera_position = aqua::CVector3(0, 75, 25);

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
	m_Camera.m_BackGraphHandle = m_BackGround->GetBackGround();

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
	m_Camera.m_BackGraphHandle = m_BackGround->GetBackGround();
	ICamera::Draw();

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
