#include "object.h"

IObject::IObject(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,"Sphere",name)
{
}

void IObject::Initialize(aqua::CVector3 position)
{
}

void IObject::Update()
{
	IGameObject::Update();
}

void IObject::Finalize()
{
	m_Model.Delete();
	IGameObject::Finalize();
}