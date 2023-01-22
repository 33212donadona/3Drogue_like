#pragma once
#include "aqua.h"
#include "../../../weapon_manager/weapon/weapon.h"
#include "../../../weapon_manager/weapon/sword/sword.h"
#include "../../../weapon_manager/magic/magic.h"
#include "../../../weapon_manager/magic/fire_ball/fire_ball.h"
#include "../unit.h"

class CEnemy;
class CStage;

class CPlayer : public IUnit
{
public:

	CPlayer(aqua::IGameObject* parent);
	~CPlayer() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	int GetAnimetionNum();

	/*!
	*  @brief 武器との衝突検知
	*
	*  @param[in] first_pos   線分の初め
	*  @param[in] end_pos     線分の終わり
	*
	*  @retval true    武器と衝突した
	*  @retval false   武器と衝突しなかった
	*/
	bool CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos);

private:

	void AnimetionWork();       //! アニメーション
	void Move();                //! 移動
	void Rotation();            //! 回転
	void Weapon();              //! 武器
	void Collision();           //! 衝突処理

private:
	static const int m_max_animetion;
	static const float m_shot_animetion_frame;
	static const float m_max_hit_point;
	static const float m_attack;


	IWeapon* m_Weapon;
	IMagic* m_Magic;
	CStage* m_Stage;
	float m_Angles;
	int   m_MagicFrame;
	int Animetion;

	bool m_ShotMagic;
};