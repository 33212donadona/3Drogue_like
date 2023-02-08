#pragma once
#include "aqua.h"
#include "../unit.h"
#include "player_anime_id.h"
#include "../../../common_data/common_data_info.h"

class CEnemy;
class CWeaponManager;
class CBagData;
class CJobManager;
class CCommonData;

enum class WEAPON_ID;
enum class JOB_ID;

class CPlayer : public IUnit
{
public:

	CPlayer(aqua::IGameObject* parent);
	~CPlayer() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	/*
	*  @brief 動きの更新
	*/
	void MoveUpdata()override;

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

	/*!
	*  @brief 角度を取得
	* 
	*  @return 角度
	*/
	float GetAngle();

	bool  GetAttackFlag();
	bool  GetStandbyFlag();
	bool  GetShotMagic();
	bool  GetCancelMagic();

	JOB_ID GetPlayerJob();

private:

	void AnimetionWork();       //! アニメーション
	void FistAnimeWork();      //! 
	void SwordAnimeWork();      //! 
	void MagicAnimeWork();      //! 
	void MoneyAnimeWork();      //! 
	void Move();                //! 移動
	void Rotation();            //! 回転
	void Weapon();              //! 武器


private:

	static const float m_shot_animetion_frame;
	static const float m_chage_max_time;
	static const float m_max_hit_point;
	static const float m_attack;

	CWeaponManager* m_WeaponManager;
	CBagData*       m_BagData;
	CJobManager*    m_JobManager;
	CCommonData*    m_CommonData;

	WEAPON_ID       m_SetingWeapon;
	JOB_ID          m_PlayerJobID;
	P_ANIME_ID      m_AnimeState;

	CommonDataInfo  m_CommonDataInfo;

	aqua::CTimer    m_ChageTime;

	float m_Angles;
	int   m_MagicFrame;

	bool m_Standby;
	bool m_ShotMagic;
	bool m_AttackFlag;
	bool m_CancelMagic;
};