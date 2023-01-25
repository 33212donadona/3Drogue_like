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
	void Draw()			override;
	void Finalize()		override;

private:
	aqua::CModel* m_SelectModel;
	CCommonData*  m_CommonData;
};