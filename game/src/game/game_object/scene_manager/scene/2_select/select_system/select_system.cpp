#include "select_system.h"
#include "../../../../common_data/common_data.h"
CSelectSystem::CSelectSystem(IGameObject* parent)
	:aqua::IGameObject(parent,"SelectSystem")
{
}

void CSelectSystem::Initialize()
{
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
}

void CSelectSystem::Update()
{
}

void CSelectSystem::Draw()
{
}

void CSelectSystem::Finalize()
{
}
