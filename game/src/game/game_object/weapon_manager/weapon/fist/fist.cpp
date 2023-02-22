#include "fist.h"
#include "../../../sound_manager/game_sound_manager.h"
#include "../../../unit_manager/unit/player/player.h"
const int CFist::m_fist_radius = 2;
const int CFist::m_enemy_radius = 3;

CFist::CFist(aqua::IGameObject* parent)
	:IWeapon(parent,"Fist")
	, m_Player(nullptr)
{
}
/*
* 初期化
*/
void CFist::Initialize()
{
	m_HitFistEffect.Create("data\\effect\\fist_attak.efkefc");
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
}
/*
* 更新
*/
void CFist::Update()
{
	if (!m_Player)
	{
		m_Player = (CPlayer*)aqua::FindGameObject("Player");
	}
	else
	{
		if (m_HitFist && m_Player->GetAttackFlag() && m_HitFistEffect.Finished())
		{
			m_HitFistEffect.position = m_FistPosition;
			m_HitFistEffect.Play();
		}
	}
	m_HitFistEffect.Update();
}
/*
* 解放
*/
void CFist::Finalize()
{
	m_HitFistEffect.Delete();
}
/*
* 衝突判定
*/
bool CFist::CheckHit(aqua::CVector3 enemy_pos)
{
	float r = m_fist_radius + m_enemy_radius;

	aqua::CVector2 distance;
	distance.x = m_FistPosition.x - enemy_pos.x;
	distance.y = m_FistPosition.z - enemy_pos.z;

	m_HitFist = distance.x * distance.x + distance.y * distance.y <= r * r;

	return m_HitFist;
}
/*
* モデルにプレイヤーの手に座標を設定
*/
void CFist::SetPosition(aqua::CVector3 position)
{
	m_FistPosition = position;
}
