#include "object.h"

IObject::IObject(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Sphere")
{
}

void IObject::Initialize(aqua::CVector3 position)
{
	m_Model.Create("data\\stage\\object", 0);
	m_Model.position = position;
	m_Model.scale = aqua::CVector3::ONE * 1.9f;
	m_Model.axis.y = 1.0f;
}

void IObject::Update()
{
}

void IObject::Finalize()
{
	m_Model.Delete();
}
