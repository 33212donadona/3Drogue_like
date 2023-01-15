#pragma once
#include "aqua.h"

class IUnit : public aqua::IGameObject
{
public:

	IUnit(aqua::IGameObject* parent,std::string name);
	~IUnit() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

	float GetAttack();
	aqua::CVector3 GetPosition();

public:

	enum class STATE
	{
		MOVE,
		DEAD
	};

private:

	float m_HitPoint;
	float m_Attack;

protected:

	aqua::CVector3 m_position;
	aqua::CModel m_UnitModel;
	int m_MaxAnimetion;
	float m_MaxHitPoint;
};

