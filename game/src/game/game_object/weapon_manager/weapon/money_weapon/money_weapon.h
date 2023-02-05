#pragma once
#include "../weapon.h"

class CPlayer;

class CMoneyWeapon :public IWeapon
{
public:

	CMoneyWeapon(aqua::IGameObject* parent);
	~CMoneyWeapon() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool CheckHit(aqua::CVector3 enemy_pos)override;

	void SetPosition(aqua::CVector3 position)override;

private:
	static const int m_money_radius;
	static const int m_enemy_radius;

	aqua::CVector3  m_MoneyPosition;
	aqua::CEffect3D m_MoneyEffect;

	bool            m_HitMoney;

	CPlayer* m_Player;
};