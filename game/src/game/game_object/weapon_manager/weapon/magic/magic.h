#pragma once
#include "../weapon.h"

class CPlayer;

enum class MAGIC_STATE
{
	INVOKE_MAGIC,
	KEEP_MAGIC,
	FINISHED_MAGIC
};

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
	int             m_MoveDistance;

	MAGIC_STATE     m_MagicState;

	CPlayer*        m_Player;

	aqua::CEffect3D m_MagicFirstEffect;
	aqua::CEffect3D m_MagicKeepEffect;
	aqua::CEffect3D m_MagicEndEffect;
};