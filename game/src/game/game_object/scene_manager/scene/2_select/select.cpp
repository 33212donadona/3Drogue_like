#include "select.h"
#include "../../../select_back_ground/select_back_ground.h"

CSelect::CSelect(IGameObject* parent)
	:IScene(parent,"Select")
{
}

void CSelect::Initialize()
{
	aqua::CreateGameObject<CSelectBackGround>(this);

	aqua::IGameObject::Initialize();
}

void CSelect::Update()
{
	// スペースでゲームシーンへ移動
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::GAMEMAIN);
	}
	aqua::IGameObject::Update();
}

void CSelect::Draw()
{
	aqua::IGameObject::Draw();
}

void CSelect::Finalize()
{
	aqua::IGameObject::Finalize();
}
