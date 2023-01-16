#include "object.h"

IObject::IObject(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Sphere")
{
}

void IObject::Initialize(aqua::CVector3 position)
{
	m_Model.Create("data\\stage\\object_rock", 0);
	m_Model.position = position;
	m_Model.scale = aqua::CVector3::ONE * 1.5f;
	m_Model.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);

	m_Model.angles.x = aqua::DegToRad((float)std::pow(-1.0f,aqua::Rand(1, 0)) * 90.0f);
}

void IObject::Update()
{
}

void IObject::Finalize()
{
	m_Model.Delete();
}
