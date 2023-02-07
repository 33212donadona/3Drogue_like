#pragma once
#include "../weapon.h"

class CPlayer;

class CFist :public IWeapon
{
public:

	CFist(aqua::IGameObject* parent);
	~CFist() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool CheckHit(aqua::CVector3 enemy_pos)override;

	void SetPosition(aqua::CVector3 position)override;

private:
	static const int m_fist_radius;
	static const int m_enemy_radius;

	bool m_HitFist;

	CPlayer* m_Player;

	aqua::CVector3 m_FistPosition;
	aqua::CEffect3D m_HitFistEffect;

};