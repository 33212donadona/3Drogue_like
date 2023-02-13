#include "controller_ui.h"
#include "../../../common_data/common_data.h"

CControllerUI::CControllerUI(aqua::IGameObject* parent)
	:IUserInterface(parent,"Controller")
{
}

void CControllerUI::Initialize()
{
	m_ControllerSprite.Create("data\\game_graph\\XBox_ê‡ñæ.png");
	m_ControllerSprite.position = aqua::GetWindowSize();
	m_ControllerSprite.position.x -= m_ControllerSprite.GetTextureWidth();
	m_ControllerSprite.position.y -= m_ControllerSprite.GetTextureHeight();
}

void CControllerUI::Update()
{
}

void CControllerUI::Draw()
{
	m_ControllerSprite.Draw();
}

void CControllerUI::Finalize()
{
	m_ControllerSprite.Delete();
}
