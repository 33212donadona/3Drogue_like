#include "ui_manager.h"
#include "ui/job_icom/job_icom.h"
#include "ui/hitpoint_ui/hitpoint_ui.h"
#include "ui/controller_ui/controller_ui.h"

CUIManager::CUIManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent ,"UIManager")
{
}
/*
* 初期化
*/
void CUIManager::Initialize()
{
	aqua::CreateGameObject<CHitPointUI>(this);
	aqua::CreateGameObject<CJobIcon>(this);
	aqua::CreateGameObject<CControllerUI>(this);

	aqua::IGameObject::Initialize();
}
/*
* 更新
*/
void CUIManager::Update()
{
	aqua::IGameObject::Update();
}
/*
* 描画
*/
void CUIManager::Draw()
{
	aqua::IGameObject::Draw();
}
/*
* 解放
*/
void CUIManager::Finalize()
{
	aqua::IGameObject::Finalize();
}
