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
	*  @brief �����̍X�V
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

	static const float m_summon_max_time;       //! ���������̍ő厞��
	static const float m_not_damege_max_time;   //! ���������̍ő厞��
	static const float m_dead_max_time;         //! ���S�����̍ő厞��
	static const float m_first_position_height; //! ���߂̍���
	static const int   m_max_dead_effect;       //! �ő厀�S�G�t�F�N�g��
	STATE              m_State;                 //! ���j�b�g�̏��
	aqua::CTimer       m_EffectTime;            //! �G�t�F�N�g����
	aqua::CTimer       m_NotDamageTime;         //! ���G���Ԏ���
	aqua::CEffect3D    m_SummonEffect;          //! �����G�t�F�N�g
	aqua::CEffect3D*   m_DeadEffect;            //! ���S�G�t�F�N�g

	int                m_StateDamageFrame;      //! �_���[�W��Ԃ̃t���[��
	float              m_PrevHitPoint;
	/*
	*  @brief ����
	*/
	void Summon();

	/*
	*  @brief  ���S����
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

