#include "object.h"

IObject::IObject(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,"Sphere",name)
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