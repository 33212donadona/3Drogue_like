#pragma once
#include "aqua.h"

class CStage;

class IUnit : public aqua::IGameObject
{
public:

	IUnit(aqua::IGameObject* parent,std::string name);
	~IUnit() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

	/*
	*  @brief 動きの更新
	*/
	virtual void MoveUpdata(){};

	float GetAttack();
	float GetMaxHitPoint();
	float GetHitPoint();
	aqua::CVector3 GetPosition();
	bool  GetDead();

public:

	enum class STATE
	{
		SUMMON,
		MOVE,
		DAMAGE,
		DEAD
	};

	STATE GetState();

private:

	static const float m_summon_max_time;       //! 召喚処理の最大時間
	static const float m_not_damege_max_time;   //! 召喚処理の最大時間
	static const float m_dead_max_time;         //! 死亡処理の最大時間
	static const float m_first_position_height; //! 初めの高さ
	static const int   m_max_dead_effect;       //! 最大死亡エフェクト数
	STATE              m_State;                 //! ユニットの状態
	aqua::CTimer       m_EffectTime;            //! エフェクト時間
	aqua::CTimer       m_NotDamageTime;         //! 無敵時間時間
	aqua::CEffect3D    m_SummonEffect;          //! 召喚エフェクト
	aqua::CEffect3D*   m_DeadEffect;            //! 死亡エフェクト

	int                m_StateDamageFrame;      //! ダメージ状態のフレーム
	float              m_PrevHitPoint;
	/*
	*  @brief 召喚
	*/
	void Summon();

	/*
	*  @brief  死亡処理
	*/
	void Dead();

protected:

	float m_HitPoint;
	float m_MaxHitPoint;
	float m_Attack;
	aqua::CVector3 m_position;
	aqua::CModel m_UnitModel;
	int m_MaxAnimetion;
	bool DeadFlag;
	CStage* m_Stage;

};

