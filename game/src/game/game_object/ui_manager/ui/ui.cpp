#include "ui.h"

IUserInterface::IUserInterface(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent, name, "UserInterface")
{
}

void IUserInterface::Initialize()
{
	if (m_user_interface_name != "")
		m_UserInterfaceSprite.Create(m_user_interface_name);
}

void IUserInterface::Draw()
{
	if (m_user_interface_name != "")
	{
		if (m_UserInterfaceSprite.GetResourceHandle() > -1)
		{
			m_UserInterfaceSprite.Draw();
		}
	}
}