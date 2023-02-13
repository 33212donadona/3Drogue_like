#include "game_camera.h"
#include "../../unit_manager/unit/player/player.h"
#include "../../input/input.h"
#include "../../common_data/common_data.h"
const aqua::CVector3 CGameCamera::m_camera_position = aqua::CVector3(0, 75, 25);

/*
 *  コンストラクタ
 */
CGameCamera::CGameCamera(aqua::IGameObject* parent)
	:ICamera(parent, "GameCamera")
{
}
/*
 *  初期化
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

	m_Range_of_VisionSprite.Create("data\\game_graph\\視界_2.png");

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
	ICamera::Draw();

	m_Range_of_VisionSprite.Draw();

#ifdef AQUA_DEBUG
	//aqua::CLabel cl;
	//cl.Create(20);
	//cl.color = aqua::CColor::BLUE;
	//cl.position.y = 200.0f;
	//cl.text = std::to_string(m_PlayerClass->GetAnimetionNum()) + "\n" +
	//	"x:" + std::to_string(m_Camera.camera_position.x) + "\n"+
	//	"y:" + std::to_string(m_Camera.camera_position.y) + "\n"+
	//	"z:" + std::to_string(m_Camera.camera_position.z) + "\n"+
	//	"Ho:" + std::to_string(Input::Horizotal()) + "\n"+
	//	"V:" + std::to_string(Input::Vertical()) + "\n"	+
	//	"E:" + std::to_string(m_CommonData->GetData().easy) + "\n"+
	//	"N:" + std::to_string(m_CommonData->GetData().nomal) + "\n"+
	//	"Ha:" + std::to_string(m_CommonData->GetData().hard) + "\n"	+
	//	"Next:" + std::to_string((int)m_CommonData->GetData().stage_lever) + "\n"	+
	//	"C:" + std::to_string(m_CommonData->GetData().crea_stage) + "\n"+
	//	"S:" + std::to_string(m_CommonData->GetData().crea_target);
	//
	//cl.Draw();
	//cl.Delete();
#endif

}

void CGameCamera::Finalize()
{
	m_Range_of_VisionSprite.Delete();
	ICamera::Finalize();
}
