#include "sword.h"

const std::string m_file_pass = "data\\model\\weapon\\sword";

CSword::CSword(aqua::IGameObject* parent)
	:IWeapon(parent,"Sword")
{
}

void CSword::Initialize()
{
	m_SwordModel.Create("data\\model\\weapon\\sword",0);
}

void CSword::Update()
{
}

void CSword::Finalize()
{
	m_SwordModel.Delete();
}

bool CSword::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_SwordModel.GetBoneCapsuleCollision("Collision.000", first_pos, end_pos,3).HitFlag || 
		m_SwordModel.GetBoneCapsuleCollision("Collision.001", first_pos, end_pos, 3).HitFlag;
}

void CSword::SetMatrix(aqua::CMatrix& matrix)
{
	m_SwordModel.SetMatrix(matrix);
}
