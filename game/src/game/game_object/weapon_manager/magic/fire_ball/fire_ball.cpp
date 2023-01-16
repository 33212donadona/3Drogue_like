#include "fire_ball.h"

CFireBall::CFireBall(aqua::IGameObject* parent)
	:IMagic(parent,"FireBall")
{
}

void CFireBall::Initialize()
{
	m_MagicEffectName = "data\\effect\\magic_3.efk";
	IMagic::Initialize();
}

void CFireBall::Update()
{
	IMagic::Update();
}

void CFireBall::Finalize()
{
	IMagic::Finalize();
}
