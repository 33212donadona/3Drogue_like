#include "object_tower.h"

CObjectTower::CObjectTower(aqua::IGameObject* parent)
	:IObject(parent,"ObjectTower")
{
}

void CObjectTower::Initialize(aqua::CVector3 position)
{
	m_Model.Create("data\\stage\\object_tower", 0);
	m_Model.position = position;
	m_Model.position.y -= 8.5f;
	m_Model.scale = aqua::CVector3::ONE * 2.25f;
	m_Model.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);
}

void CObjectTower::Update()
{
}

void CObjectTower::Finalize()
{
	IObject::Finalize();
}
