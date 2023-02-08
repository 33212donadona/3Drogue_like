#pragma once
#include "aqua.h"
#include "../unit.h"

class CPlayer;
class IWeapon;

class CEnemy : public IUnit
{
public:
	CEnemy(aqua::IGameObject* parent);
	~CEnemy() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	/*
	*  @brief 動きの更新
	*/
	void MoveUpdata()override;

private:
	void Algorithms();
	static const float m_max_hit_point;
	static const float m_attack;
	IWeapon* m_Weapon;
	CPlayer* m_PlayerModel;
	bool m_DamageFlag;                 //! 連続ダメージを防ぐ
};