#include "object_rock.h"

CObjectRock::CObjectRock(aqua::IGameObject* parent)
	:IObject(parent,"ObjectRock")
{
}

void CObjectRock::Initialize(aqua::CVector3 position)
{
	m_Model.Create("data\\stage\\object_rock", 0);
	m_Model.position = position;
	m_Model.position.y -= 8.5f;
	m_Model.scale = aqua::CVector3::ONE * 2.25f;
	m_Model.initial_axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
	m_Model.initial_angles = aqua::DegToRad(aqua::Rand(360, 1));
	m_Model.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);
	m_Model.angles = aqua::DegToRad((float)std::pow(-1.0f, aqua::Rand(1, 0)) * 90.0f);
}

void CObjectRock::Update()
{
}

void CObjectRock::Finalize()
{
	IObject::Finalize();
}
