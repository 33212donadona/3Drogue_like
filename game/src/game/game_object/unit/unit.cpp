#include "unit.h"

CUnit::CUnit(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Unit")
{
}

void CUnit::Initialize()
{
	m_UnitModel.Create("data\\model\\Bot", 4);

	m_UnitModel.scale = aqua::CVector3::ONE * 0.1f;

	Animetion = 0;

	m_UnitModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);
}

void CUnit::Update()
{
	AnimetionWork();

	m_UnitModel.position.x += aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::D);
	m_UnitModel.position.y += aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN);
	m_UnitModel.position.z += aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) - aqua::keyboard::Button(aqua::keyboard::KEY_ID::W);

	m_UnitModel.position.x = aqua::Limit(m_UnitModel.position.x, -95.0f, 95.0f);
	m_UnitModel.position.y = aqua::Limit(m_UnitModel.position.y, -95.0f, 95.0f);
	m_UnitModel.position.z = aqua::Limit(m_UnitModel.position.z, -95.0f, 95.0f);

	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W))
		m_UnitModel.angles.x = aqua::DegToRad(0);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		m_UnitModel.angles.x = aqua::DegToRad(270);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S))
		m_UnitModel.angles.x = aqua::DegToRad(180);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		m_UnitModel.angles.x = aqua::DegToRad(90);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) && aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		m_UnitModel.angles.x = aqua::DegToRad(45);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) && aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		m_UnitModel.angles.x = aqua::DegToRad(315);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) && aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		m_UnitModel.angles.x = aqua::DegToRad(135);
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) && aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		m_UnitModel.angles.x = aqua::DegToRad(225);

		//Animetion += aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::O) - aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::P);
		Animetion = aqua::Limit(Animetion, 0, 3);

	m_UnitModel.AnimationUpdata(Animetion);
}

void CUnit::Draw()
{
	IGameObject::Draw();
}

void CUnit::Finalize()
{
	m_UnitModel.Delete();
}

int CUnit::GetAnimetionNum()
{
	return Animetion;
}

aqua::CVector3 CUnit::GetPosition()
{
	return m_UnitModel.position;
}

void CUnit::AnimetionWork()
{
	if (
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::W) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::A) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::S) ||
		aqua::keyboard::Button(aqua::keyboard::KEY_ID::D)
		)
	{
		Animetion = 2;
	}
	else
		Animetion = 0;
}