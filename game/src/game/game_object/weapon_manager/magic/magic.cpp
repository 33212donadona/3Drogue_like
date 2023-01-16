#include "magic.h"

IMagic::IMagic(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent, name, "Magic")
	, m_MagicRotationi(0)
{
}

void IMagic::Initialize()
{
	m_MagicEffect.Create(m_MagicEffectName);
	m_MagicEffect.scale = aqua::CVector3::ONE;
	m_MagicEffect.Play();
}

void IMagic::Update()
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::C) && m_MagicEffect.Finished())
		m_MagicEffect.Play();

	m_MagicEffect.position = m_Position;
	m_MagicEffect.Update();
}

void IMagic::Finalize()
{
	m_MagicEffect.Delete();
}

void IMagic::SetPosition(aqua::CVector3 position)
{
	if (m_PrevPosition != position)
		m_Position = position;

	if (m_PrevPosition != m_Position)
		m_PrevPosition = m_Position;
}
