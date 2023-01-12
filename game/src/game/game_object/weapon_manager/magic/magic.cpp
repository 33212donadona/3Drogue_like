#include "magic.h"

IMagic::IMagic(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent, name, "Magic")
	, m_MagicRotationi(0)
{
}

void IMagic::Initialize()
{
	m_MagicEffect.Create(m_MagicEffectName);
	m_MagicEffect.scale = aqua::CVector3::ONE * 10;
	m_MagicEffect.Play();
	m_MagicEffect.SetPlayingSpeed(10.0f);
	m_MagicSphele.Create();
}

void IMagic::Update()
{
	m_MagicRotationi = (m_MagicRotationi++) % 180;

	m_MagicEffect.rotation = aqua::DegToRad((float)m_MagicRotationi);

	if (m_MagicEffect.Finished())
		m_MagicEffect.Play();
	m_MagicEffect.position = m_Position;
	m_MagicSphele.Updata(m_Position, 1);
	m_MagicEffect.Update();
}

void IMagic::Draw()
{
	m_MagicEffect.Draw();
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
