#pragma once
#include "aqua.h"
#include "../unit.h"
#include "enemy_anime_id.h"

class CPlayer;
class IWeapon;
class CBagData;

class CEnemy : public IUnit
{
public:
	CEnemy(aqua::IGameObject* parent);
	~CEnemy() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	/*
	*  @brief �����̍X�V
	*/
	void MoveUpdata()override;

private:
	void Algorithms();

	void AnimetionWark();
private:
	static const float m_max_hit_point;
	static const float m_attack;

	IWeapon* m_Weapon;
	CPlayer* m_PlayerModel;
	CBagData* m_BagData;

	ENEMY_ANIME_ID m_AnimetionID;

	aqua::CModel   m_Sword;
	aqua::CTimer   m_AttackCoolTime;

	bool m_DamageFlag;                 //! �A���_���[�W��h��
};