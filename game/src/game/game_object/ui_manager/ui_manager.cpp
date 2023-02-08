#include "ui_manager.h"
#include "ui/job_icom/job_icom.h"
#include "ui/hitpoint_ui/hitpoint_ui.h"

CUIManager::CUIManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent ,"UIManager")
{
}

void CUIManager::Initialize()
{
	aqua::CreateGameObject<CHitPointUI>(this);
	aqua::CreateGameObject<CJobIcon>(this);

	aqua::IGameObject::Initialize();
}

void CUIManager::Update()
{
	aqua::IGameObject::Update();
}

void CUIManager::Draw()
{
	aqua::IGameObject::Draw();
}

void CUIManager::Finalize()
{
	aqua::IGameObject::Finalize();
}
