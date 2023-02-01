#pragma once
#include "../weapon.h"

class CPlayer;

class CMagic : public IWeapon
{
public:
	CMagic(aqua::IGameObject* parent);
	~CMagic() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool CheckHit(aqua::CVector3 enemy_pos)override;

	void SetPosition(aqua::CVector3 position)override;

private:

	void Shot();

private:
	static const int m_effect_radius;
	static const int m_enemy_radius;

	bool            m_HitMagic;
	bool            m_FindPlayer;
	float           m_Angles;

	CPlayer*        m_Player;

	aqua::CEffect3D m_MagicFirstEffect;
	aqua::CEffect3D m_MagicKeepEffect;
	aqua::CEffect3D m_MagicEndEffect;
	int             m_MoveDistance;
};