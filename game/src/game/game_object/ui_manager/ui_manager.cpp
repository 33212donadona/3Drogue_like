#include "ui_manager.h"
#include "ui/job_icom/job_icom.h"
#include "ui/hitpoint_ui/hitpoint_ui.h"
#include "ui/controller_ui/controller_ui.h"

CUIManager::CUIManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent ,"UIManager")
{
}
/*
* ‰Šú‰»
*/
void CUIManager::Initialize()
{
	aqua::CreateGameObject<CHitPointUI>(this);
	aqua::CreateGameObject<CJobIcon>(this);
	aqua::CreateGameObject<CControllerUI>(this);

	aqua::IGameObject::Initialize();
}
/*
* XV
*/
void CUIManager::Update()
{
	aqua::IGameObject::Update();
}
/*
* •`‰æ
*/
void CUIManager::Draw()
{
	aqua::IGameObject::Draw();
}
/*
* ‰ğ•ú
*/
void CUIManager::Finalize()
{
	aqua::IGameObject::Finalize();
}
