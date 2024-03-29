#include "controller_ui.h"
#include "../../../common_data/common_data.h"

CControllerUI::CControllerUI(aqua::IGameObject* parent)
	:IUserInterface(parent,"Controller")
{
}
/*
* 初期化
*/
void CControllerUI::Initialize()
{
	m_ControllerSprite.Create("data\\game_graph\\XBox_説明.png");
	m_ControllerSprite.position = aqua::GetWindowSize();
	m_ControllerSprite.position.x -= m_ControllerSprite.GetTextureWidth();
	m_ControllerSprite.position.y -= m_ControllerSprite.GetTextureHeight();
}
/*
* 描画
*/
void CControllerUI::Draw()
{
	m_ControllerSprite.Draw();
}
/*
* 解放
*/
void CControllerUI::Finalize()
{
	m_ControllerSprite.Delete();
}
