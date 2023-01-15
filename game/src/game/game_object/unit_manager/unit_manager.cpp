#include "unit_manager.h"
#include "unit/player/player.h"
#include "unit/enemy/enemy.h"


CUnitManager::CUnitManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"UnitManager")
{
}

void CUnitManager::Initialize()
{
	aqua::CreateGameObject<CPlayer>(this);
	aqua::CreateGameObject<CEnemy>(this);

	IGameObject::Initialize();
}

void CUnitManager::Update()
{
	IGameObject::Update();
}

void CUnitManager::Finalize()
{
	IGameObject::Finalize();
}
