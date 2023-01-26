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

private:
	static const aqua::CVector2 m_object_space;
	static const int m_max_animetion;

	aqua::CModel* m_SelectModel;
	aqua::CModel  m_SelectPointer;
	CCommonData*  m_CommonData;
};