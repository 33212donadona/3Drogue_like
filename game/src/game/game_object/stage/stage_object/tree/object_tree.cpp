#include "object_tree.h"

CObjectTree::CObjectTree(aqua::IGameObject* parent)
	:IObject(parent,"ObjectTree")
{
}

void CObjectTree::Initialize(aqua::CVector3 position)
{
	m_Model.Create("data\\stage\\object_tree", 0);
	m_Model.position = position;
	m_Model.position.y -= 2.0f;
	m_Model.scale = aqua::CVector3::ONE * 0.5f;
	m_Model.axis  = aqua::CVector3(0.0f, 1.0f, 0.0f);
	m_Model.angles = aqua::DegToRad(aqua::Rand(360, 1));
}

void CObjectTree::Update()
{
}

void CObjectTree::Finalize()
{
	m_Model.Delete();
}