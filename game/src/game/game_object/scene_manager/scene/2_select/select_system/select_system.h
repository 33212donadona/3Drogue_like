#pragma once
#include "aqua.h"

class CCommonData;

class CSelectSystem : public aqua::IGameObject
{
public:
	CSelectSystem(IGameObject* parent);
	~CSelectSystem() = default;

	void Initialize()	override;
	void Update()		override;
	void Finalize()		override;

	bool GetDecisionSelsectLavel();

	int  GetNowLavel();  //! 今選択しているレベル
	int  GetPrevLavel(); //! 前フレームで選択していたレベル

	aqua::CVector3 GetTargetPosition();

private:

	static const aqua::CVector2 m_object_space;
	static const int m_max_animetion;
	static const float m_max_easing_time;

	aqua::CModel*	m_SelectModel;
	aqua::CModel	m_SelectPointer;
	aqua::CTimer	m_EasingTimer;
	CCommonData*	m_CommonData;
	int				m_CountModel;
	int				m_SelsectLevel;
	int				m_PrevSelsectLevel;

};